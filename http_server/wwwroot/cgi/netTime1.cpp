#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include"netTime.h"

#define MAX 1024

void mycal(char *buf){
    int year,month,day;
    int days;
    sscanf(buf,"year=%d&month=%d&day=%d&days=%d",&year,&month,&day, &days);//sscanf是把一个字符串格式化输出到某几个变量里
    Date date(year,month,day);
    //sscanf(buf,"year2=%d&month2=%d&day2=%d\n",&year2,&month2,&day2);
    printf("<html>\n");
    printf("<body>\n");
    printf("<meta charset=utf-8>");
    printf("<h3>%d-%d-%d 往后 %d  天是 </h3>",year,month,day,days);
    Date d2 = date + days;
    d2.Display();
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
