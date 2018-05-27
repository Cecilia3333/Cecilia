#include <stdio.h>
#include<stdint.h>

void Swap(int* a,int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void BubbleSort(int arr[],size_t size){
    if(size <= 1)
        return;
    size_t bound = 0;//[0,bound)表示有序元素，[bound,size)表示待排序元素
    for(;bound < size;bound++){
        size_t cur = size-1;
        for(;cur > bound;cur--){
            if(arr[cur] < arr[cur-1])
                Swap(&arr[cur],&arr[cur-1]);
        }
    }
    return;
}


void SelectSort(int arr[],size_t size){
    if(size <= 1)
        return;
    size_t bound = 0;
    for(;bound < size;bound++){
        size_t cur = bound+1;
        for(;cur < size;cur++){
            if(arr[bound] > arr[cur])
                Swap(&arr[bound],&arr[cur]);
        }
    }
    return;
}


void InsertSort(int arr[],size_t size){
    if(size <= 1)
        return;
    size_t bound = 1;
    //[0,bound)表示有序元素，[bound,size)表示待排序元素
    //插入排序将前面的有序区间当成一个线性表，然后将bound位置的元素插入到线性表中的合适位置
    for(;bound < size;bound++){
        int bound_value = arr[bound];
        size_t cur = bound;
        for(;cur > 0;cur--){
            if(arr[cur-1] > bound_value)//进行搬运
                arr[cur] = arr[cur-1];
            else//说明已找到合适的位置
                break;
    }
        arr[cur] = bound_value;
    }
}


void AdjustDown(int arr[],size_t size,size_t index){
    size_t parent = index;
    size_t child = 2*parent+1;
    while(child < size){//升序排序，建立大堆
        if(child+1 < size && arr[child+1] > arr[child])
            child += 1;//child指向了左右子树中较大的
        if(arr[parent] < arr[child])
            Swap(&arr[parent],&arr[child]);
        parent = child;
        child = 2*parent+1;
    }
    return;
}


void HeapCreate(int arr[],size_t size){
    if(size <= 1)
        return;
    size_t i = (size-1-1)/2;
    for(;i > 0;i--)
        AdjustDown(arr,size,i);
    AdjustDown(arr,size,0);
    return;
} 


void HeapPop(int arr[],size_t heap_size){
    if(heap_size <= 1)
        return;
    Swap(&arr[0],&arr[heap_size-1]);
    AdjustDown(arr,heap_size-1,0);
    return;
}

void HeapSort(int arr[],size_t size){
    if(size <= 1)
        return;
    HeapCreate(arr,size);//创建堆的函数
    size_t i = 0;
    for(;i < size;i++)
        HeapPop(arr,size-i);
    //size-i表示数组中哪部分区间符合堆的规则
    //即第i次删除前，[0，size-i)都是堆
    return;
}


void ShellSort(int arr[],int64_t size){
    int64_t gap = size/2;//使用希尔序列
    for(;gap > 0;gap /= 2){//生成步长序列
        int64_t bound = gap;
        for(;bound < size;bound++){//进行插入排序
            int bound_value = arr[bound];
            int64_t cur = bound;
            for(;cur  >= gap;cur -= gap){//线性表的查找和搬运
                //cur-=gap表示找到同组元素中的上一个元素
                if(arr[cur-gap] > bound_value)//进行搬运
                    arr[cur] = arr[cur-gap];
                else//找到了
                    break;
            }
            arr[cur] = bound_value;
        }
    }
    return;
}


int main(){
    int arr[] = {9,5,2,7};
    int len = sizeof(arr)/sizeof(arr[0]);
    ShellSort(arr,len);
    int i = 0;
    for(;i < len;i++)
        printf("%d ",arr[i]);
    printf("\n");
    return 0;
}
