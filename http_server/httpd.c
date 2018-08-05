#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<arpa/inet.h>
#include<pthread.h>

#define MAX 1024
#define HOME_PAGE "index.html"
#define ERROR_PAGE "error.html"

static void Usage(const char* proc){
    printf("Usage: %s port\n",proc);
}


static int startup(int port){
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("socket");
        exit(2);
    }

    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));//避免TIME_WAIT导致的bind失败

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);

    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
        perror("bind");
        exit(3);
    }

    if(listen(sock,5) < 0){
        perror("listen");
        exit(4);
    }
    return sock;
}

static int get_line(int sock,char line[],int size){
    //回车换行可能有三种形式：\r\n,\r,\n
    //这里我们在HTTP内部统一按\n处理
    //具体操作方法：一次获取一个字符，碰到上面三种就停下来
    int c = 'a';//初始化为非\n的字符即可
    int i = 0;
    ssize_t s = 0;
    while(i < size-1 && c != '\n'){
        s = recv(sock,&c,1,0);//从sock读取，每次读一个字符
        if(s > 0){//说明读成功了
            if(c == '\r'){
                //这里有两种情况，一种是\r\n，一种是\r
                //我们要统一将其转化成\n处理
                if(recv(sock,&c,1,MSG_PEEK) > 0){//使用MSG_PEEK选项窥探下一个字符（不将底层数据拿上来，只是读取下一个字符的内容）
                    if(c != '\n'){//如果下一个字符不是\n,说明是\r的情况，此时直接将\r转成\n即可
                        c = '\n';
                    }else{//是\r\n的情况
                        recv(sock,&c,1,0);//将\n拿上来
                        //此时c里面放的是\n
                        //c里面原本是\r，现在覆盖成\n，将相当于是把\r\n转化成了\n
                    }
                }
            }
            //由于三种情况最终都要转化成\n处理，所以\n本身不需要进行转化，也就不需要特殊处理
            line[i++] = c;//当读到\n时，就跳出循环了，即读到了一行
        }
        else{//读失败
            break;
        }
    }
    line[i] = '\0';
    return i;
}

void clear_header(int sock){//这个函数要做的就是一直从缓冲区里读数据，直到读到空行就停下来,这就有效的解决了tcp底部的粘包问题
    char line[MAX]; 
    do{
        get_line(sock,line,sizeof(line));
        printf("%s",line);
    }while(strcmp(line,"\n") != 0);
}

void echo_www(int sock,char *path,int size,int *err){
//此时HTTP只读取了第一行，剩下的还在读缓冲区中放着
//由于HTTP是基于请求相应的，如果不把请求读完，就无法正常的进行相应
//所以首先要将HTTP的请求读完
    clear_header(sock);
    //走到这里我们就将请求处理完了
    //接下来处理响应
    int fd = open(path,O_RDONLY);
    if(fd < 0){
        *err = 404;
        return;
    }
    char line[MAX];
    sprintf(line,"HTTP/1.0 200 OK\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"Content-Type:text/html\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"\r\n");
    send(sock,line,strlen(line),0);
    sendfile(sock,fd,NULL,size);
    close(fd);
}

void echo_error(int errCode,char *path){
    switch(errCode){
        case 404:
            strcat(path,ERROR_PAGE);
            break;
        default:
            break;
    }
}

int exe_cgi(int sock,char path[],char method[],char *query_string){
    char line[MAX];
    int content_length = -1;

    char method_env[MAX/32];
    char query_string_env[MAX];
    char content_length_env[MAX/16];

    if(strcasecmp(method,"GET") == 0){
        clear_header(sock);
    }else{
        do{
            get_line(sock,line,sizeof(line));
            if(strncmp(line,"Content-Length: ",16) == 0){
                content_length = atoi(line+16);//获取报文长度
            }
        }while(strcmp(line,"\n") != 0);//读到空行为止
        if(content_length == -1){//不符合标准
            return 404;
        }
        //空行已经读完
    }

    sprintf(line,"HTTP/1.0 200 OK\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"Content-Type:text/html\r\n");
    send(sock,line,strlen(line),0);
    sprintf(line,"\r\n");
    send(sock,line,strlen(line),0);
    
    //站在子进程的角度
    int input[2];
    int output[2];

    pipe(input);
    pipe(output);

    pid_t id = fork();//创建子进程进行线程替换
    if(id < 0){
        return 404;
    }else if(id == 0){//子进程
        //父进程需要给子进程以下数据：
        //method
        //GET[query_string]
        //POST[content_length]
        //可以将这些数据设置为环境变量，由于环境变量具有全局属性，所以程序替换时不会替换环境变量，且会被子进程继承
          
        close(input[1]);//关闭input的写
        close(output[0]);//关闭output的读
        
        dup2(input[0],0);
        dup2(output[1],1);

        sprintf(method_env,"METHOD=%s",method);
        putenv(method_env);

        if(strcasecmp(method,"GET") == 0){
            sprintf(query_string_env,"QUERY_STRING=%s",query_string);
            putenv(query_string_env);
        }

        else{//POST
            sprintf(content_length_env,"CONTENT_LENGTH=%d",content_length);
            putenv(content_length_env);
        }

        printf("method:%s",method);
        execl(path,path,NULL);//执行path字符串所代表的文件路径
        exit(1);
    }else{//父进程
        close(input[0]);
        close(output[1]);

        char c;
        if(strcasecmp(method,"POST") == 0){
            int i = 0;
            while(i < content_length){
                read(sock,&c,1);
                write(input[1],&c,1);
                i++;
            }
        }

        while(read(output[0],&c,1) > 0){
            send(sock,&c,1,0);
        }

        waitpid(id,NULL,0);

        //结束后关闭对应的文件描述符
        close(input[1]);
        close(output[0]);
    }
    return 200;
}

static void* handler_request(void *arg){
    int sock = (int)arg;
    char line[MAX];
    char method[MAX/32];
    char url[MAX];
    char path[MAX];
    int errCode = 200;
    int cgi = 0;
    char* query_string = NULL;

#ifdef debug//这一部分用于调试   
    do{
        get_line(sock,line,sizeof(line));
        printf("%s",line);
    }while(strcmp(line,"\n") != 0);

#else//这一部分是主逻辑

    if(get_line(sock,line,sizeof(line)) < 0){
        errCode = 404;
        goto end;
    }

    //提取方法字段
    int i = 0;
    int j = 0;
    //此时line里面放的是请求行
    //即line[] = GET / HTTP /1.1
    //方法字段即为GET
    while(i < sizeof(method)-1 && j < sizeof(line) && !isspace(line[j])){
        method[i] = line[j];
        i++;
        j++;
    }
    method[i] = '\0';

    //在这里我们只处理GET或POST方法
    if(strcasecmp(method,"GET") == 0){
    }else if(strcasecmp(method,"POST") == 0){
        cgi = 1;
    }else{
        errCode = 404;
        goto end;
    }

    while(j < sizeof(line) && isspace(line[j])){//处理空格
        j++;
    }
    
    //此时j就走到了非空格字段
    i= 0;
    //提取url字段
    while(i < sizeof(url)-1 && j < sizeof(line) && !isspace(line[j])){
        url[i] = line[j];
        i++;
        j++;
    }
    url[i] = '\0';

    //GET方法有带参和不带参两种情况
    //当GET方法中带参时，处理的方法为cgi方法，此时cgi=1
    //所以我们定义了一个query_string来指向GET方法中url带参的那一部分
    if(strcasecmp(method,"GET") == 0){
        query_string = url;
        while(*query_string){
            if(*query_string == '?'){
                //url中,?后面的是参数部分
                *query_string = '\0';//将url与参数分离开
                query_string++;
                //走到这里，说明GET带参，所以要以cgi方法处理
                cgi = 1;
                break;
            }
            //说明没有找到？
            query_string++;
        }
    }
    //走到这里，我们就可以清楚：
    //method[GET or POST]
    //cgi[0 or 1]
    //usl里面放的是某个资源的路径
    //query_string里面要么为空，要么带的是参数

    //接下来要验证请求的资源是否存在
    //在验证url中请求的资源是否存在时，我们要在路径前面拼上wwwroot
    sprintf(path,"wwwroot%s",url);//将输出的信息按照printf的格式输出到特定的字符串中
    //当url为/ 时，经过拼接，就变成了wwwroot/,这相当于是在请求根目录，这是不可行的，所以当请求是这种情况时，我们将首页返回。
    if(path[strlen(path)-1] == '/'){//最后一个元素以 / 结尾
        strcat(path,HOME_PAGE);
    }
    
    printf("method:%s,path:%s\n",method,path);

    //走到这里说明资源已经定位，接下来我们就要验证要请求资源的合法性
    struct stat st;
    if(stat(path,&st) < 0){
        errCode = 404;
        goto end;
    }else{
        if(S_ISDIR(st.st_mode)){//若请求的是一个目录,返回首页
            strcat(path,HOME_PAGE);
        }else{
        //若请求的资源具有可执行权限，则以cgi的方式运行
            if((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH)){//拥有者、所属组、其他中任何一个具有可执行权限，就要以cgi方式运行
                cgi = 1;
            }
        }

        //走到这里，我们就可以肯定，要请求的资源是存在的，而且是否以cgi方式运行也已经确定下来了
        if(cgi){//以cgi方式运行
            errCode = exe_cgi(sock,path,method,query_string);
        }else{//不以cgi方式运行————GET方法、不带参,要返回的就是一个普通的文件
            echo_www(sock,path,st.st_size,&errCode);
        }
    }

#endif
end:
    if(errCode != 200){
        echo_error(errCode,path);
    }
    close(sock);
}


int main(int argc,char* argv[]){
    if(argc != 2){
        Usage(argv[0]);
        return 1;
    }
    int listen_sock = startup(atoi(argv[1]));
    signal(SIGPIPE,SIG_IGN);

    for(;;){
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);

        if(new_sock < 0){
            perror("accept");
            continue;
        }
        //走到这里表示新连接已经获取成功
        pthread_t id;
        pthread_create(&id,NULL,handler_request,(void *)new_sock);
        pthread_detach(id);

    }
}
