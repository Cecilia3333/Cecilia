#include"bloom_filter.h"
#include"hash_func.h"
#define PRINT_HEAD printf("\n============%s============\n",__FUNCTION__);

void TestInit(){
    PRINT_HEAD;
    BloomFilter bf;
    BloomFilterInit(&bf);
    printf("bloom_hash[0] expect %p,actual %p\n",SDBMHash,bf.bloom_hash[0]);
    printf("bloom_hash[1] expect %p,actual %p\n",BKDRHash,bf.bloom_hash[1]);
    return;
}

void TestDestroy(){
    PRINT_HEAD;
    BloomFilter bf;
    BloomFilterInit(&bf);
    BloomFilterDestroy(&bf);
    printf("bloom_hash[0] expect NULL,actual %p\n",bf.bloom_hash[0]);
    printf("bloom_hash[1] expect NULL,actual %p\n",bf.bloom_hash[1]);
    return;
}

void TestInsertAndIsExit(){
    PRINT_HEAD;
    BloomFilter bf;
    BloomFilterInit(&bf);
    BloomFilterInsert(&bf,"haha");
    BloomFilterInsert(&bf,"hehe");
    int ret = BloomFilterIsExit(&bf,"haha");
    printf("ret expect 1,actual %d\n",ret);
    ret = BloomFilterIsExit(&bf,"hehe");
    printf("ret expect 1,actual %d\n",ret);
    ret = BloomFilterIsExit(&bf,"hello");
    printf("ret expect 0,actual %d\n",ret);
    return;
}

int main(){
    TestInit();
    TestDestroy();
    TestInsertAndIsExit();
    return 0;
}

