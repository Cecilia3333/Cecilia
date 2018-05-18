#pragma once

#include<stdio.h>
#include<stddef.h>

#define HashMaxSize 1000

typedef int KeyType;
typedef int ValType;

typedef enum{
    Empty,
    Valid,
    Deleted,
}Stat;

typedef struct HashElem{
    KeyType key;
    ValType value;
    Stat stat;
}HashElem;

typedef size_t (*HashFunc)(KeyType key); 

typedef  struct HashTable{
    HashElem data[HashMaxSize];
    size_t size;
    HashFunc func;
}HashTable;

size_t HashFuncDefault(KeyType key);
void HashPrint(HashTable* ht,const char* msg);
void HashInit(HashTable* ht,HashFunc hash_func);
void HashDestroy(HashTable* ht);
void HashInsert(HashTable* ht,KeyType key,ValType value);
int HashFind(HashTable* ht,KeyType key,ValType* value);
void HashRemove(HashTable* ht,KeyType key);
