#include <stdio.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<string.h>  
#include<netinet/in.h>  
#include<stdlib.h>  
  
void service(int sock){  
    char buf[128];  
    struct sockaddr_in client;  
    socklen_t len=sizeof(client);  
    while(1){  
            ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);  
            if(s > 0){  
                        buf[s]=0;  
                        printf("[%s:%d]:%s\n",inet_ntoa(client.sin_addr));  
                    }  
        }  
}  
  
int main(int argc,char* argv[]){  
    if(argc != 3){  
            printf("Usage:%s [ip] [port]\n",argv[0]);  
            return 3;  
        }  
    int sock=socket(AF_INET,SOCK_DGRAM,0);  
    if(sock < 0){  
            perror("socket");  
            return 1;  
        }  
    struct sockaddr_in local;  
    local.sin_family = AF_INET;  
    local.sin_port = htons(atoi(argv[2]));  
    local.sin_addr.s_addr = inet_addr(argv[1]);  
  
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){  
            perror("bind");  
            return 2;  
        }  
    service(sock);  
} 
