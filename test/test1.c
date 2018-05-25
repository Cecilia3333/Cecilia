#include <stdio.h>

int myatoi(char arr[],int len){
    if(len == 0)
        return 0;
    int flag = 1;
    if(arr[0] == '-'){
        flag = -1;
        arr[0] = '0';
    }
    else if(arr[0] == '+'){
        flag = 1;
        arr[0] = '0';
    }
    int sum = 0;
    int i = 0;
    for(;i < len;i++){
        if(arr[i] < '0' || arr[i] > '9'){
            sum = 0;
            break;
        }
        sum = sum*10+arr[i]-'0';
    }
    return flag*sum;
}

int main(){
    char arr[10] = {0};
    int i = 0;
    for(;i < 10;i++){
    scanf("%c",&arr[i]);
    }
    int len = sizeof(arr)/sizeof(arr[0]);
    int ret = myatoi(arr,len);
    printf("%d\n",ret);
    return 0;
}
