#pragma once
#include<stdio.h>  
#include<stdlib.h>  
#include<stddef.h>  
  
#define MAX_ROW 6  
#define MAX_COL 6  
     
typedef struct Maze{  
    int map[MAX_ROW][MAX_COL];  
}Maze;  
  
typedef struct Point{  
    int row;  
    int col;  
}Point;  
  
typedef Point SeqStackType;  
  
typedef struct SeqStack{  
    SeqStackType *data;  
    size_t size;  
    size_t capacity;  
}SeqStack; 
