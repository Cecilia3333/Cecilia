#include"search.h"

void SearchTreeInit(SearchNode** pRoot){
    if(pRoot == NULL)
        return;
    *pRoot = NULL;
    return;
}

SearchNode* CreateSearchNode(SearchNodeType value){
    SearchNode* new_node = (SearchNode*)malloc(sizeof(SearchNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

void DestroySearchNode(SearchNode* node){
    free(node);
}

void SearchTreeDestroy(SearchNode** pRoot){
    if(pRoot == NULL)
        return;
    SearchNode* root = *pRoot;
    SearchTreeDestroy(&root->lchild);
    SearchTreeDestroy(&root->rchild);
    DestroySearchNode(root);
    *pRoot = NULL;
    return;
}

void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert){
    if(pRoot == NULL)//非法输入
        return;
    if(*pRoot == NULL){//空树
        SearchNode* new_node = CreateSearchNode(to_insert);
        *pRoot = new_node;
        return;
    }
    //对于树非空的情况，递归插入
    SearchNode* cur = *pRoot;
    if(to_insert < cur->data){//若要插入的数据小于根节点的值，则往左子树中插入
        SearchTreeInsert(&cur->lchild,to_insert);
    }
    else if(to_insert > cur->data){//若要插入的数据大于根节点的值，则往右子树中插入
        SearchTreeInsert(&cur->rchild,to_insert);
    }
    else{//插入的元素与根节点的值相同
        //约定二叉搜索树中所有元素均不重复，返回表示不作任何动作，插入失败
        return;
    }
}

SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find){
    if(to_find < root->data){//递归查找左子树
        return SearchTreeFind(root->lchild,to_find);
    }
    else if(to_find > root->data){//递归查找右子树
        return SearchTreeFind(root->rchild,to_find);
    }
    else{
        return root;
    }
}

void PreOrder(SearchNode* root){//先序遍历
    if(root == NULL)
        return;
    printf("%c ",root->data);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
    return;
}

void InOrder(SearchNode* root){//中序遍历
    if(root == NULL)
        return;
    InOrder(root->lchild);
    printf("%c ",root->data);
    InOrder(root->rchild);
    return;
}

void SearchTreePrintChar(SearchNode* root,const char* msg){
    printf("[%s]\n",msg);
    printf("先序遍历：");
    PreOrder(root);
    printf("\n");
    printf("中序遍历：");
    InOrder(root);
    printf("\n");
    return;
}

void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove){
    if(pRoot == NULL)//非法输入
        return;
    if(*pRoot == NULL)//空树
        return;
    SearchNode* root = *pRoot;
    if(to_remove <  root->data){//递归查找左子树
        SearchTreeRemove(&root->lchild,to_remove);
        return;
    }
    else if(to_remove >  root->data){//递归查找右子树
        SearchTreeRemove(&root->rchild,to_remove);
        return;
    }
    else{//分情况讨论
        if(root->lchild == NULL && root->rchild == NULL){//要删除的节点无左右子树
            *pRoot = NULL;
            DestroySearchNode(root);
            return;
        }
        else if(root->lchild != NULL && root->rchild == NULL){//要删除的节点只有左子树
            *pRoot = root->lchild;
            DestroySearchNode(root);
            return;
        }
        else if(root->lchild == NULL && root->rchild != NULL){//要删除的节点只有右子树
            *pRoot = root->rchild;
            DestroySearchNode(root);
            return;
        }
        else{//要删除的节点有左右子树
            SearchNode* min = root->rchild;
            while(min->lchild != NULL){//先找到右子树中的最小节点
                min = min->lchild;
            }
            root->data = min->data;//将要删除的节点的值与最小节点的值交换
            SearchTreeRemove(&root->rchild,min->data);//从当前节点的右子树出发，尝试递归的删除刚刚被交换的值
            return;
        }
    }
    return;
}

void SearchTreeInsert1(SearchNode** pRoot,SearchNodeType to_insert){
    if(pRoot == NULL)
        return;
    if(*pRoot == NULL){//单独处理空树的情况
        *pRoot = CreateSearchNode(to_insert);
        return;
    }
    //对于非空的树，先找到插入的位置，把要插入元素的父节点记录下来
    SearchNode* cur = *pRoot;//新元素要放置的位置
    SearchNode* pre = NULL;//新元素的父节点
    while(1){
        if(cur == NULL)//找到插入的位置，跳出循环
            break;
        if(to_insert < cur->data){
            pre = cur;
            cur = cur->lchild;
        }
        else if(to_insert > cur->data){
            pre = cur;
            cur = cur->rchild;
        }
        else{//发现相同的元素，按约定：二叉搜索树中的所有元素均不重复，直接插入失败
            return;
        }
    }
    SearchNode* new_node = CreateSearchNode(to_insert);
    if(new_node->data < pre->data){
       pre->lchild = new_node; 
    }
    else{
        pre->rchild = new_node;
    }
    return;
}

SearchNode* SearchTreeFind1(SearchNode* root,SearchNodeType to_find){
    SearchNode* cur = root;
    while(1){
        if(cur == NULL)//空树
            return NULL;
        if(to_find < cur->data){
            cur = cur->lchild;
        }
        else if(to_find > cur->data){
            cur = cur->rchild;
        }
        else{
            break;
        }
    }
    return cur;
}

void SearchTreeRemove1(SearchNode** pRoot,SearchNodeType to_remove){
    if(pRoot == NULL)
        return;
    if(*pRoot == NULL)
        return;
    //先找到要删除的节点
    SearchNode* to_remove_node = *pRoot;
    SearchNode* parent = NULL;
    while(to_remove_node != NULL){
        if(to_remove < to_remove_node->data){
            parent = to_remove_node;
            to_remove_node = to_remove_node->lchild;
        }
        else if(to_remove > to_remove_node->data){
            parent = to_remove_node;
            to_remove_node = to_remove_node->rchild;
        }
        else{//找到了要删除的节点
            break;
        }
    }
    //若找到，分情况：
    if(to_remove_node->lchild == NULL && to_remove_node->rchild == NULL){//左右子树均为空
        if(to_remove_node == *pRoot)//根节点即为要删除的节点
            *pRoot = NULL;
        else{//根节点不是要删除的节点
            if(to_remove_node->data < parent->data)
                parent->lchild = NULL;
            else
                parent->rchild = NULL;
        }
        DestroySearchNode(to_remove_node);
    }
    else if(to_remove_node->lchild != NULL && to_remove_node->rchild == NULL){//只有左子树
         if(to_remove_node == *pRoot)
            *pRoot = to_remove_node->lchild;
        else{
            if(to_remove_node->data < parent->data)
                parent->lchild = to_remove_node->lchild;
            else
                parent->rchild = to_remove_node->lchild;
        }
        DestroySearchNode(to_remove_node);
    }
    else if(to_remove_node->lchild == NULL && to_remove_node->rchild != NULL){//只有右子树
         if(to_remove_node == *pRoot)
            *pRoot = to_remove_node->rchild;
        else{
            if(to_remove_node->data < parent->data)
                parent->lchild = to_remove_node->rchild;
            else
                parent->rchild = to_remove_node->rchild;
        }
        DestroySearchNode(to_remove_node);
    }
    else{//同时有左右子树
        SearchNode* min = to_remove_node->lchild;
        SearchNode* min_parent = to_remove_node;
        while(min->lchild != NULL){
            min_parent = min;
            min = min->lchild;
        }//循环结束，min指向to_remove_node右子树的最小值
        to_remove_node->data = min->data;
        if(min->data < min_parent->data)//min为min_parent的左子树
            min_parent->lchild = min->rchild;
        else//min为min_parent的右子树
            min_parent->rchild = min->rchild;
        DestroySearchNode(min);
        return;
    }
    return;
}
