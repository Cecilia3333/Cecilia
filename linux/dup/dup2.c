#include <stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd = open("./log",O_CREAT | O_RDWR);
    if(fd < 0){
        perror("open");
        return 1;
    }
    close(1);
    dup2(fd,1);
    
    for(;;){
        char buf[1024] = {0};
        ssize_t num = read(0,buf,sizeof(buf)-1);
        if(num < 0){
            perror("read");
            continue;
        }
        printf("%s",buf);
        fflush(stdout);
    }
    return 0;
}
