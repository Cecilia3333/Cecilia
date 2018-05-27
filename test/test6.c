#include <stdio.h>

int ReversePair(int* arr,int len){
    if(arr == NULL || len <= 0)
        return 0;
    int count = 0;
    int i = 0;
    for(;i < len;i++){
        int j = i+1;
        for(;j < len;j++){
            if(arr[i] > arr[j])
                count++;
        }
    }
    return count%1000000007;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,0};
    int len = sizeof(arr)/sizeof(arr[0]);
    int ret = ReversePair(arr,len);
    printf("%d\n",ret);
    return 0;
}
