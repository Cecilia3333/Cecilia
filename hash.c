#include "hash.h"

size_t HashFuncDefault(KeyType key){
    return key % HashMaxSize;
}

HashElem* CreateElem(KeyType key,ValType value){
    HashElem* new_node = (HashElem*)malloc(sizeof(HashElem));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void DestroyElem(HashElem* node){
    free(node);
}

void HashInit(HashTable* ht,HashFunc hash_func){
    if(ht == NULL)
        return;
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for(;i < HashMaxSize;++i){
        ht->data[i] = NULL;
    }
    return;
}

void HashDestroy(HashTable* ht){
    if(ht == NULL)
        return;
    ht->size = 0;
    ht->func = NULL;
    //遍历所有链表，进行释放操作
    size_t i = 0;
    for(;i < HashMaxSize;i++){
        HashElem* cur = ht->data[i];
        while(cur != NULL){
            HashElem* next = cur->next;
            DestroyElem(cur);
            cur = next;
        }
    }
    return;
}

HashElem* HashBucketFind(HashElem* head,KeyType to_find){
    HashElem* cur = head;
    for(;cur != NULL;cur = cur->next){
        if(cur->key == to_find)
            break;
    }
    return cur;
}

int HashBucketFindEx(HashElem* head,KeyType to_find,HashElem** pre_node,HashElem** cur_node){
    HashElem* cur = head;
    HashElem* pre = NULL;
    for(;cur != NULL;pre = cur,cur = cur->next){
        if(cur->key == to_find)
            break;
    }
    if(cur == NULL)
        return 0;
    *pre_node = pre;
    *cur_node = cur;
    return 1;
}

void HashInsert(HashTable* ht,KeyType key,ValType value){
    if(ht == NULL)
        return;
    //根据key值计算offset
    size_t offset = ht->func(key);
    //在offset对应的链表中查找看当前的key是否存在
    //若存在，就认为插入失败
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret != NULL)//此时说明存在了重复的key值，认为插入失败
        return;
    //若不存在，就使用头插进行插入
    HashElem* new_node = CreateElem(key,value);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    //++size
    ++ht->size;
    return;
}

void HashPrint(HashTable* ht,const char* msg){
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < HashMaxSize;++i){
        if(ht->data[i] == NULL)
            continue;
        printf("i = %lu\n",i);
        HashElem* cur = ht->data[i];
        for(;cur != NULL;cur = cur->next){
            printf("[%d:%d]",cur->key,cur->value);
        }
        printf("\n");
    }
}

int HashFind(HashTable* ht,KeyType key,ValType* value){
    if(ht == NULL || value == NULL)
        return 0;
    //根据key计算offset
    size_t offset = ht->func(key);
    //找到对应offset的链表，遍历链表尝试找到其中的元素
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret == NULL)
        return 0;
    *value = ret->value;
    return 1;
}

void HashRemove(HashTable* ht,KeyType key){
    if(ht == NULL)
        return;
    if(ht->size == 0)
        return;
    //根据key计算offset
    size_t offset = ht->func(key);
    //通过offset找到对应的链表，
    //在链表中找到指定元素并进行删除
    HashElem* pre = NULL;
    HashElem* cur = NULL;
    int ret = HashBucketFindEx(ht->data[offset],key,&pre,&cur);
    if(ret == 0)//未找到，删除失败
        return;
    if(pre == NULL)//要删除的节点是链表的头结点
        ht->data[offset] = cur->next;
    else{
        //要删除的元素不是链表头节点
        pre->next = cur->next;
    }
    DestroyElem(cur);
    //--size;
    --ht->size;
    return;
}



