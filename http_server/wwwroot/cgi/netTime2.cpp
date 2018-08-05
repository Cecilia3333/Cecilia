#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include"netTime.h"

#define MAX 1024

void mycal(char *buf){
    int year1,month1,day1;
    int year2,month2,day2;
    sscanf(buf,"year1=%d&month1=%d&day1=%d&year2=%d&month2=%d&day2=%d",&year1,&month1,&day1, &year2,&month2,&day2);//sscanf是把一个字符串格式化输出到某几个变量里
    Date date1(year1,month1,day1);
    Date date2(year2,month2,day2);
    //sscanf(buf,"year2=%d&month2=%d&day2=%d\n",&year2,&month2,&day2);
    printf("<html>\n");
    printf("<body>\n");
    printf("<meta charset=utf-8>");
    printf("<h3>%d-%d-%d 距离 %d-%d-%d 相差 ",year2,month2,day2,year1,month1,day1);
    int days = date2 - date1;
    printf("%d天</h3>\n",days);
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
