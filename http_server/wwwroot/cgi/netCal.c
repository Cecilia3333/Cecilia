#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>

#define MAX 1024

void mycal(char *buf){
    //firstdata=100&lastdata=20
    int x,y;
    sscanf(buf,"x=%d&y=%d",&x,&y);//sscanf是把一个字符串格式化输出到某几个变量里

    printf("<html>\n");
    printf("<body>\n");
    printf("<h3>%d + %d = %d</h3>\n",x,y,x+y);  
    printf("<h3>%d - %d = %d</h3>\n",x,y,x-y);      
    printf("<h3>%d * %d = %d</h3>\n",x,y,x*y);  
    if(y == 0){
          printf("<h3>%d / %d = %d</h3>\n",x,y,-1);
          printf("<h3>%d %% %d = %d</h3>\n",x,y,-1);
    }else{
    printf("<h3>%d / %d = %d</h3>\n",x,y,x/y);  
    printf("<h3>%d %% %d = %d</h3>\n",x,y,x%y);
    }
    printf("</body>\n");
    printf("</html>\n");
    

}

int main(){
    char buf[MAX] = {0};
    if(getenv("METHOD")){
        if(strcasecmp(getenv("METHOD"),"GET") == 0){
            strcpy(buf,getenv("QUERY_STRING"));
        }else{
            int content_length = atoi(getenv("CONTENT_LENGTH"));
            int i = 0;
            char c;
            for(i = 0;i < content_length;i++){
                read(0,&c,1);
                buf[i] = c;
            }
            buf[i] = '\0';
        }
    }
    
    mycal(buf);
    return 0;
}
