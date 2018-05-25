#include <stdio.h>
#include<string.h>

int main(){
    char arr[100];
    int n,i,p,j;
    char s;
    printf("please enter the string:");
    fgets(arr,100,stdin);
    printf("please enter the length:");
    scanf("%d",&n);
    printf("please enter the location:");
    scanf("%d",&p);
    for(i = 0;i < n-p-1;i++){
        s = arr[n-1];
        for(j = n-1;j >=1;j--)
            arr[j] = arr[j-1];
        arr[0] = s;
    }
    printf("the result is:%s",arr);
}
