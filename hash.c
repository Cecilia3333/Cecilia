#include"hash.h"

size_t HashFuncDefault(KeyType key){
    return key % HashMaxSize;
}

void HashInit(HashTable* ht,HashFunc hash_func){
    if(ht == NULL)
        return;
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for(;i < HashMaxSize;++i){
        ht->data[i].stat = Empty;
    }
    return;
}

void HashDestroy(HashTable* ht){
    if(ht == NULL)
        return;
    ht->size = 0;
    ht->func = NULL;
    return;
}

void HashInsert(HashTable* ht,KeyType key,ValType value){
    if(ht == NULL)//非法输入
        return;
    if(ht->size >= 0.8*HashMaxSize)//判定hash表能否继续插入（根据负载因子判定），这里我们假定负载因子为0.8
        return;
    size_t offset = ht->func(key);//根据key计算offset
    //从offset位置开始线性的往后查找，找到第一个状态为Empty的元素来进行插入
    while(1){
        if(ht->data[offset].stat != Valid){
            //此时找到了一个合适的位置来放置要插入的元素
            ht->data[offset].stat = Valid;
            ht->data[offset].key = key;
            ht->data[offset].value = value;
            //++size
            ++ht->size;
            return;
        }
        else if(ht->data[offset].stat == Valid && ht->data[offset].key == key){
            //hash表中存在了一个key相同的元素，此时我们单纯的认为插入失败
            return;
        }
        else{
            ++offset;
            if(offset >= HashMaxSize)
                offset = 0;
        }
    }
    //如果发现了key相同的元素，此时认为插入失败
    return;
}

void HashPrint(HashTable* ht,const char* msg){
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < HashMaxSize;++i){
        if(ht->data[i].stat == Empty){
            continue;
        }
        printf("[%lu   %d:%d]  ",i,ht->data[i].key,ht->data[i].value);
    }
    printf("\n");
}

int HashFind(HashTable* ht,KeyType key,ValType* value){
    if(ht == NULL || value == NULL)
        return 0;
    if(ht->size == 0)
        return 0;
    size_t offset = ht->func(key);//根据key计算出offset
    while(1){//从offset开始往后进行查找，每次取得一个元素，使用key进行比较
        //如果找到了key相同的元素，此时直接把value返回，并且认为查找成功
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid){
            //找到了
            *value = ht->data[offset].value;
            return 1;
        }
        else if(ht->data[offset].stat == Empty)
            //如果发现当前元素是一个空元素，此时认为查找失败
            return 0;
        else{
            //如果发现当前的key不相同，就继续往后查找
            ++offset;
            offset = offset>=HashMaxSize?0:offset;
        }
    }
    return 0;
}

void HashRemove(HashTable* ht,KeyType key){
    if(ht == NULL)
        return;
    if(ht->size == 0)
        return;
    size_t offset = ht->func(key);//根据key计算offset
    //从offset开始，依次判定当前元素的key和要删除元素的key是否相同
    while(1){
        //若当前的key就是要删除的key，删除当前元素即可，将要删除元素的状态标记为Deleted
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid){
            ht->data[offset].stat = Deleted;
            --ht->size;
            return;
        }
        //若当前元素为空元素，则key在hash表中没有找到，删除失败，直接返回即可
        else if(ht->data[offset].stat == Empty)
            return;
        else{
            ++offset;
            offset = offset>=HashMaxSize?0:offset;
        }
    }
    return;
}


