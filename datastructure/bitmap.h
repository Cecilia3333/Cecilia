#pragma once 
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<inttypes.h>
typedef uint64_t BitmapType;
typedef struct Bitmap{
    BitmapType* data;
    BitmapType capacity;
}Bitmap;

void BitmapInit(Bitmap* bm,uint64_t capacity);
void BitmapDestroy(Bitmap* bm);
void BitmapSet(Bitmap* bm,uint64_t index);
void BitmapUnset(Bitmap* bm,uint64_t index);
void BitmapFill(Bitmap* bm);
void BitmapClear(Bitmap* bm);
int BitmapTest(Bitmap* bm,BitmapType index);
void GetOffSet(uint64_t index,uint64_t* n,uint64_t* offset);
