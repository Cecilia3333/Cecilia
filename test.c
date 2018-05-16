#include"heap.h"

#define PRINT_HEAD printf("\n============%s============\n",__FUNCTION__);

extern Greater(HeapType a,HeapType b);

void TestInit(){
    PRINT_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("size expect 0,actual %lu\n",heap.size);
}

void TestInsert(){
    PRINT_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'e');
    HeapPrintChar(&heap,"插入六个元素");
    HeapDestroy(&heap);
    printf("size expect 0,actual %lu\n",heap.size);
}

void TestRoot(){
    PRINT_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'e');
    HeapType value = 0;
    int ret = HeapRoot(&heap,&value);
    printf("ret expect 1,actual %d\n",ret);
    printf("value expect f,actual %c\n",value);
}

void TestErase(){
    PRINT_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'f');
    HeapInsert(&heap,'e');
    HeapPrintChar(&heap,"插入六个元素");
    HeapErase(&heap);
    HeapPrintChar(&heap,"删除一个元素");
}

void TestCreate(){
    PRINT_HEAD;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapType array[] = {'a','d','c','b','f','e'};
    size_t size = sizeof(array)/sizeof(array[0]);
    HeapCreate(&heap,array,size);
    HeapPrintChar(&heap,"创建堆");
}

void TestSort(){
    Heap heap;
    HeapType array[] = {'a','d','c','b','f','e'};
    size_t size = sizeof(array)/sizeof(array[0]);
    HeapSort(array,size);
    HeapPrintChar(&heap,"堆排序");
}

int main(){
    TestInit();
    TestInsert();
    TestRoot();
    TestErase();
    TestCreate();
    TestSort();
    return 0;
}
