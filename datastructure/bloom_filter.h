#pragma once

#include"bitmap.h"

#define BloomHashCount 2
typedef uint64_t(*BloomHash)(const char*);//此处定义了一个布隆过滤器的哈希函数，将字符串转成下标

typedef struct BloomFilter{
    Bitmap bm;
    BloomHash bloom_hash[BloomHashCount];
}BloomFilter;

void BloomFilterInit(BloomFilter* bf);
void BloomFilterDestroy(BloomFilter* bf);
void BloomFilterInsert(BloomFilter* bf,const char* str);
int BloomFilterIsExit(BloomFilter* bf,const char* str);
