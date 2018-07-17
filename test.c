#include <stdio.h>
#include<stdlib.h>
#define N 4
void rotate(int arr[N][N],int a,int b,int c,int d){
    for(int i = 0;i < d-b;++i){
        int tmp = arr[a][b+i];
        arr[a][b+i] = arr[c-i][b];
        arr[c-i][b] = arr[c][d-i];
        arr[c][d-i] = arr[a+i][d];
        arr[a+i][d] = tmp;
    }
}

void rotateArr(int arr[N][N]){
    int a = 0;
    int b = 0;
    int c = N-1;
    int d = N-1;

    while(a < c){
       rotate(arr,a++,b++,c--,d--);
    }
}

void show(int arr[N][N]){
    for(int i = 0;i < N;++i){
        for(int j = 0;j < N;++j){
            printf("%-3d",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int arr[N][N];
    int num = 1;
    for(int  i = 0;i < N;++i){
        for(int j = 0;j < N;++j)
            arr[i][j] = num++;
    }
    show(arr);
    rotateArr(arr);
    printf("\n");
    show(arr);

    return 0;
}
