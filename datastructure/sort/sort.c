#include"seqstack.h"
#include<string.h>

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


void _MergeArray(int arr[],int64_t beg,int64_t mid,int64_t end,int *tmp){
    int64_t cur1 = beg;
    int64_t cur2 = mid;
    int64_t tmp_index = beg;
    while(cur1 < mid && cur2 < end){
        if(arr[cur1] < arr[cur2])
            tmp[tmp_index++] = arr[cur1++];
        else
            tmp[tmp_index++] = arr[cur2++];
    }
    while(cur1 < mid)
        tmp[tmp_index++] = arr[cur1++];
    while(cur2 < end)
        tmp[tmp_index++] = arr[cur2++];
    memcpy(arr+beg,tmp+beg,sizeof(int)*(end-beg));
    return;
}


void _MergeSort(int arr[],int64_t beg,int64_t end,int *tmp){
    //[beg,end)为当前要处理的数组
    if(end - beg <= 1)
        return;
    int64_t mid = beg + (end - beg) / 2;
    //将数组分成两个区间[0,mid),[mid,end)
    _MergeSort(arr,beg,mid,tmp);
    _MergeSort(arr,mid,end,tmp);
    _MergeArray(arr,beg,mid,end,tmp);
    return;
}


void MergeSort(int arr[],size_t size){
    if(size <= 1)
        return;
    int *tmp = (int*)malloc(sizeof(int) * size);//创建临时空间，用来合并元素
    _MergeSort(arr,0,size,tmp);
    free(tmp);
    return;
}


void MergeSortByLoop(int arr[],size_t size){
    if(size <= 1)
        return;
    int *tmp = (int*)malloc(sizeof(int)*size);
    size_t gap = 1;//gap表示步长，相当于每次合并两个长度为gap的有序区间
    for(;gap < size;gap *= 2){
        size_t i = 0;
        for(;i < size;i += 2*gap){//辅助完成所有长度为gap的区间的合并
        size_t beg = i;
        size_t mid = i + gap;
        size_t end = i + 2*gap;
        if(mid > size)
            mid = size;
        if(end > size)
            end = size;
        _MergeArray(arr,beg,mid,end,tmp);
        }
    }
    return;
}


int64_t Partion(int arr[],int64_t beg,int64_t end){//快速排序方法一——————交换法
    if(end - beg <= 1)
        return beg;
    int64_t left = beg;
    int64_t right = end - 1;
    int key = arr[right];//取数组的最后一个元素作为基准值
    while(left < right){
        while(left < right && arr[left] <= key)
            ++left;//从左往右找到一个大于key的元素
        while(left < right && arr[right] >= key)
            --right;//从右往左找到一个小于key的元素
        if(left < right){
            Swap(&arr[left],&arr[right]);
        }
    }
    Swap(&arr[left],&arr[end-1]);
    return left;
}


int64_t Partion2(int arr[],int64_t beg,int64_t end){//快速排序方法二——————挖坑法
    if(end - beg <= 1)
        return beg;
    int64_t left = beg;
    int64_t right = end - 1;
    int key = arr[right];//取数组最后一个元素作为基准值
    while(left < right){
        while(left < right && arr[left] <= key)
            ++left;//循环退出就意味着left指向了一个大于基准值的元素
        //就可以将这个元素填到刚才right所指向的坑里，
        //一旦赋值完成，left自身就变成了一个坑
        if(left < right)
            arr[right--] = arr[left];
        while(left < right && arr[right] >= key)
            --right;//循坏退出就意味着right指向了一个小于基准值的元素
        //就可以将这个元素填到刚才left所指向的坑里，
        //一旦赋值完成，right自身就变成了一个坑
        if(left < right)
            arr[left++] = arr[right];
    }
    //一旦left与right重合，说明整个区间整理完毕，只剩一个坑，将基准值填到left指向的坑里即可
    arr[left] = key;
    return left;
}


void _QuickSort(int arr[],int64_t beg,int64_t end){
    if(end - beg <= 1)
        return;
    int64_t mid = Partion2(arr,beg,end);//[beg,mid)左半区间，[mid,end)右半区间
    //左半区间中的元素一定小于等于右半区间中的元素
    _QuickSort(arr,beg,mid);
    _QuickSort(arr,mid,end);
    return;
}


void QuickSort(int arr[],size_t size){
    if(size <= 1)
        return;
    _QuickSort(arr,0,size);
    return;
}


void QuickSortByLoop(int arr[],size_t size){
    if(size <= 1)
        return;
    SeqStack stack;
    SeqStackInit(&stack);
    int beg = 0;
    int end = size;
    SeqStackPush(&stack,beg);
    SeqStackPush(&stack,end);
    while(1){
        int ret = GetTop(&stack,&end);
        if(ret == 0)//栈为空，说明快速排序结束
            break;
        SeqStackPop(&stack);
        GetTop(&stack,&beg);//[beg,end)相当于是即将进行快速排序，进行整理的区间
        if(end - beg <= 1)
            continue;
        int64_t mid = Partion(arr,beg,end);
        SeqStackPush(&stack,beg);
        SeqStackPush(&stack,mid);
        SeqStackPush(&stack,mid+1);
        SeqStackPush(&stack,end);
    }
    return;
}


int main(){
    int arr[] = {9,5,2,7};
    int len = sizeof(arr)/sizeof(arr[0]);
    QuickSortByLoop(arr,len);
    int i = 0;
    for(;i < len;i++)
        printf("%d ",arr[i]);
    printf("\n");
    return 0;
}
