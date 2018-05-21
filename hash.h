#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#define HashMaxSize 1000

typedef int KeyType;
typedef int ValType;

typedef struct HashElem{
    KeyType key;
    ValType value;
    struct HashElem* next;            
}HashElem; 

typedef size_t(*HashFunc)(KeyType key);

typedef  struct HashTable{
    //如果我们的hash桶上面的链表是一个不带头节点的链表，类型就用HashElem*
    //如果我们的hash桶上面的链表是一个带头节点的链表，类型就用HashElem
   HashElem* data[HashMaxSize];
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

