#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>

typedef char SearchNodeType;

typedef struct SearchNode{
    SearchNodeType data;
    struct SearchNode* lchild;
    struct SearchNode* rchild;
}SearchNode;

SearchNode* CreateSearchNode(SearchNodeType value);
void SearchTreeInit(SearchNode** pRoot);
void SearchTreeDestroy(SearchNode** pRoot);
void DestroySearchNode(SearchNode* node);
void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert);
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find);
void SearchTreePrintChar(SearchNode* root,const char* msg);
void PreOrder(SearchNode* root);
void InOrder(SearchNode* root);
void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove);
void SearchTreeInsert1(SearchNode** pRoot,SearchNodeType to_insert);
SearchNode* SearchTreeFind1(SearchNode* root,SearchNodeType to_find);
void SearchTreeRemove1(SearchNode** pRoot,SearchNodeType to_remove);
