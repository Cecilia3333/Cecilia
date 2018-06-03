#include<stdio.h>
#include <unistd.h>
#include<fcntl.h>
#include<errno.h>

void SetNoBlock(int fd){
    int fl = fcntl(fd,F_GETFL);
    if(fl < 0){
        perror("fcntl");
        return;
    }
    fcntl(fd,F_SETFL,fl | O_NONBLOCK);
    return;
}

int main(){
    SetNoBlock(0);//将标准输入设为非阻塞
    while(1){
        char buf[1024] = {0};
        ssize_t num = read(0,buf,sizeof(buf)-1);
        if(num == -1 && errno == EAGAIN){
            printf("stdin data is not ready\n");
            sleep(1);
            continue;
        }
        printf("input:%s\n",buf);
    }
    return 0;
}
