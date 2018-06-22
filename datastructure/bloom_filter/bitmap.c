#include"bitmap.h"

void BitmapInit(Bitmap* bm,uint64_t capacity){
    if(bm == NULL)
        return;
    bm->capacity = capacity;
    BitmapType size = capacity/(sizeof(bm->data[0])*8)+1;
    bm->data = (BitmapType*)malloc(sizeof(BitmapType)*size);
    memset(bm->data,0,sizeof(BitmapType)*size);
    return;
}

void BitmapDestroy(Bitmap* bm){
    if(bm == NULL)
        return;
    bm->capacity = 0;
    free(bm->data);
    return;
}

void GetOffSet(uint64_t index,uint64_t* n,uint64_t* offset){
    if(n == NULL || offset == NULL)
        return;
    *n = index / (sizeof(BitmapType)*8);
    *offset = index % (sizeof(BitmapType)*8);
    return;
}

int BitmapTest(Bitmap* bm,BitmapType index){
    if(bm == NULL )
        return 0;
    if(index >= bm->capacity)
        return 0;
    uint64_t n,offset;
    GetOffSet(index,&n,&offset);
    uint64_t ret = bm->data[n] & (0x1ul << offset);
    return ret > 0 ? 1 : 0;
}

void BitmapSet(Bitmap* bm,uint64_t index){
    if(bm == NULL)
        return;
    if(index >= bm->capacity)
        return;
    uint64_t n,offset;
    GetOffSet(index,&n,&offset);
    bm->data[n] |= (0x1ul << offset);
    return;
}

void BitmapUnset(Bitmap* bm,uint64_t index){
    if(bm == NULL)
        return;
    if(index >= bm->capacity)
        return;
    uint64_t n,offset;
    GetOffSet(index,&n,&offset);
    bm->data[n] &= ~(0x1ul << offset);
    return;
}
void BitmapFill(Bitmap* bm){
    if(bm == NULL)
        return;
    BitmapType size = bm->capacity/(sizeof(bm->data[0])*8)+1;
    memset(bm->data,0xff,sizeof(BitmapType)*size);
}
void BitmapClear(Bitmap* bm){
    if(bm == NULL)
        return;
    BitmapType size = bm->capacity/(sizeof(bm->data[0])*8)+1;
    memset(bm->data,0x0,sizeof(BitmapType)*size);
}

