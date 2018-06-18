#include <stdio.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<unistd.h>  
#include<string.h>  
#include<sys/types.h>  
#include<arpa/inet.h>  
#include<stdlib.h>  
  
#define MAX 128  
  
int Startup(char* ip,int port){  
    int sock = socket(AF_INET,SOCK_STREAM,0);  
    if(sock < 0){  
            printf("socket error!\n");  
            exit(2);  
        }  
    struct sockaddr_in local;  
    local.sin_family = AF_INET;  
    local.sin_addr.s_addr = inet_addr(ip);  
    local.sin_port = htons(port);  
  
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){  
            printf("bind error!\n");  
            exit(3);  
        }  
      
    if(listen(sock,5) < 0){  
            printf("listen error!\n");  
            exit(4);  
        }  
  
    return sock;  
}  
  
void service(int sock,char* ip,int port){  
    char buf[MAX];  
    while(1){  
            buf[0] = 0;  
            ssize_t s = read(sock,buf,sizeof(buf)-1);  
            if(s > 0){  
                        buf[s] = 0;  
                        printf("[%s:%d] say# %s\n",ip,port,buf);  
                        write(sock,buf,strlen(buf));  
                    }  
            else if(s == 0){  
                        printf("client [%s:%d] quit!\n",ip,port);  
                        break;  
                    }  
            else{  
                        printf("read error!\n");  
                        break;  
                    }  
        }  
}  
  
int main(int argc,char* argv[]){  
    if(argc != 3){  
            printf("Usage:%s [ip] [port]\n",argv[0]);  
            return 1;  
        }  
    int listen_sock = Startup(argv[1],atoi(argv[2]));  
      
    struct sockaddr_in peer;  
    char ipBuf[24];  
    for(;;){  
            ipBuf[0] = 0;  
            socklen_t len = sizeof(peer);  
            int new_sock = accept(listen_sock,(struct sockaddr*)&peer,&len);  
            if(new_sock < 0){  
                        printf("accept error!\n");  
                        continue;  
                    }  
            inet_ntop(AF_INET,(const void*)&peer.sin_addr,ipBuf,sizeof(ipBuf));  
            int p = ntohs(peer.sin_port);  
            printf("get a new connect,[%s:%d]\n",ipBuf,p);  
      
            pid_t id = fork();  
            if(id == 0){//child  
                        close(listen_sock);  
                        if(fork() > 0){  
                                        exit(0);  
                                    }  
                        service(new_sock,ipBuf,p);  
                        close(new_sock);  
                        exit(0);  
                    }  
            else if(id > 0){//father  
                        close(new_sock);  
                        waitpid(id,NULL,0);  
                    }  
            else{  
                        printf("fork error!\n");  
                        continue;  
                    }  
        }  
    return 0;  
}
