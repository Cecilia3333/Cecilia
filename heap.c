#include "heap.h"

int Greater(HeapType a,HeapType b){
    return a>b?1:0;
}

int Less(HeapType a,HeapType b){
    return a<b?1:0;
}

void HeapInit(Heap* heap,Compare cmp){
    //初始化时决定这个堆是大堆还是小堆
    heap->size = 0;
    heap->cmp = cmp;
    return;
}

void HeapDestroy(Heap* heap){
    heap->size = 0;
    heap->cmp = NULL;
    return;
}

void Swap(HeapType* a,HeapType* b){
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void AdjustUp(Heap* heap,size_t index){
    if(heap == NULL)
        return;
    size_t child = index;
    size_t parent = (child-1)/2;
    while(child > 0){
        if(!heap->cmp(heap->data[parent],heap->data[child])){
            Swap(&heap->data[parent],&heap->data[child]);
        }
        else{
            break;
        }
        child = parent;
        parent = (child-1)/2;
    }
    return;
}

void HeapInsert(Heap* heap,HeapType value){
    if(heap == NULL)
        return;
    if(heap->size >= HeapMaxSize)
        return;
    heap->data[heap->size++] = value;
    AdjustUp(heap,heap->size-1);
    return;
}

void HeapPrintChar(Heap* heap,const char* msg){
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < heap->size;i++){
        printf("[%c | %lu]  ",heap->data[i],i);
    }
    printf("\n");
}

int HeapRoot(Heap* heap,HeapType* value){
    if(heap == NULL)
        return 0;
    if(heap->size == 0)
        return 0;
    *value = heap->data[0];
    return 1;
}

void AdjustDown(Heap* heap,size_t index){
    if(heap == NULL)
        return;
    size_t parent = index;
    size_t child = 2*index+1;
    while(child < heap->size){
        if(child+1 < heap->size && heap->cmp(heap->data[child+1],heap->data[child])){
            child = child+1;
        }
        if(heap->cmp(heap->data[child],heap->data[parent])){
            Swap(&heap->data[child],&heap->data[parent]);
        }
        else{
            break;
        }
        parent = child;
        child = 2*parent+1;
    }
}

void HeapErase(Heap* heap){
    if(heap == NULL)
        return;
    if(heap->size == 0)
        return;
    Swap(&heap->data[0],&heap->data[heap->size-1]);
    --heap->size;
    AdjustDown(heap,0);
}

void HeapCreate(Heap* heap,HeapType array[],size_t size){
    if(heap == NULL)
        return;
    size_t i = 0;
    for(;i < size; i++){
        HeapInsert(heap,array[i]);
    }
    return;
}

void HeapSort(HeapType array[],size_t size){
    Heap heap;
    HeapInit(&heap,Greater);
    HeapCreate(&heap,array,size);
    while(heap.size > 0){
        HeapErase(&heap);
    }
    memcpy(array,heap.data,size*sizeof(HeapType));
    return;
}


