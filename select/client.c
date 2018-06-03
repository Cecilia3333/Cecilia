#include <stdio.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<unistd.h>  
#include<string.h>  
#include<sys/types.h>  
#include<stdlib.h>  
#include<string.h>  
  
#define MAX 128  
  
int main(int argc,char* argv[]){  
    if(argc != 3){  
            printf("Usage:%s [ip] [port]\n",argv[0]);  
            return 1;  
        }  
    int sock = socket(AF_INET,SOCK_STREAM,0);  
    if(sock < 0){  
            printf("socket error!\n");  
            return 2;  
        }  
  
    struct sockaddr_in server;  
    server.sin_family = AF_INET;  
    server.sin_port = htons(atoi(argv[2]));  
    server.sin_addr.s_addr = inet_addr(argv[1]);  
  
    if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0){  
            printf("connect error!\n");  
            return 3;  
        }  
  
    char buf[MAX];  
    while(1){  
            printf("please Enter# ");  
            fflush(stdout);  
            read(0,buf,sizeof(buf)-1);  
            /*if(s > 0){  
                    buf[s-1] = 0;  
                    if(strcmp("quit",buf) == 0){  
                                printf("client quit!\n");  
                                break;  
                            }*/  
                    ssize_t write_size = write(sock,buf,strlen(buf));
                    if(write_size < 0){
                        perror("write");
                        continue;
                    }
                    ssize_t s = read(sock,buf,sizeof(buf)-1);
                    if(s < 0){
                        perror("read");
                        continue;
                    }
                    if(s == 0){
                        printf("server close!\n");
                        break;
                    }

                    buf[s] = 0;  
                    printf("server Echo# %s\n",buf); 
        }  
    close(sock);  
    return 0;  
}  
