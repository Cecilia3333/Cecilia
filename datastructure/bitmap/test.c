#include"bitmap.h"
#define PRINT_HEAD printf("\n============%s============\n",__FUNCTION__);

void TestInit(){
    PRINT_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    printf("capacity ecpect 100,actual %lu\n",bm.capacity);
    printf("data expect 0,actual %lu\n",bm.data[0]);
}

void TestDestroy(){
    PRINT_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapDestroy(&bm);
    printf("capacity ecpect 0,actual %lu\n",bm.capacity);
    printf("data expect NULL,actual %p\n",bm.data[0]);
}

void TestSet(){
    PRINT_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    uint64_t  ret =  BitmapTest(&bm,50);
    printf("ret expect 1,actual %lu\n",ret);
    ret =  BitmapTest(&bm,10);
    printf("ret expect 0,actual %lu\n",ret);
}

void TestUnset(){
    PRINT_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    uint64_t  ret =  BitmapTest(&bm,50);
    printf("ret expect 1,actual %lu\n",ret);
    BitmapUnset(&bm,50);
    ret =  BitmapTest(&bm,50);
    printf("ret expect 0,actual %lu\n",ret);
}

void TestFill(){
    PRINT_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapFill(&bm);
    uint64_t  ret =  BitmapTest(&bm,50);
    printf("ret expect 1,actual %lu\n",ret);
    ret =  BitmapTest(&bm,0);
    printf("ret expect 1,actual %lu\n",ret);
    ret = BitmapTest(&bm,99);
    printf("ret expect 1,actual %lu\n",ret);
}

void TestClear(){
    PRINT_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapFill(&bm);
    uint64_t  ret =  BitmapTest(&bm,50);
    printf("ret expect 1,actual %lu\n",ret);
    ret =  BitmapTest(&bm,0);
    printf("ret expect 1,actual %lu\n",ret);
    ret = BitmapTest(&bm,99);
    printf("ret expect 1,actual %lu\n",ret);
    BitmapClear(&bm);
    ret =  BitmapTest(&bm,50);
    printf("ret expect 0,actual %lu\n",ret);
    ret =  BitmapTest(&bm,0);
    printf("ret expect 0,actual %lu\n",ret);
    ret = BitmapTest(&bm,99);
    printf("ret expect 0,actual %lu\n",ret);
}

int main(){
    TestInit();
    TestDestroy();
    TestSet();
    TestUnset();
    TestFill();
    TestClear();
    return 0;
}
