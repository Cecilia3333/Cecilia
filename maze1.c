#include"maze.h"  
  
int map[MAX_ROW][MAX_COL]={  
    {0,1,0,0,0,0},  
    {0,1,1,1,0,0},  
    {0,1,0,1,1,0},  
    {0,1,1,0,0,0},  
    {0,0,1,0,0,0},  
    {0,0,1,0,0,0}  
};  
  
void MazeInit(Maze* maze){  
    if(maze == NULL)  
        return;  
    size_t i = 0;  
    for(;i < MAX_ROW;i++){  
            size_t j = 0;  
            for(;j < MAX_COL;j++){  
                        maze->map[i][j] = map[i][j];  
                    }  
        }  
    return;  
}  
  
void MazePrint(Maze* maze){//打印迷宫  
    if(maze == NULL)  
        return;  
    size_t i = 0;  
    for(;i < MAX_ROW;i++){  
            size_t j = 0;  
            for(;j < MAX_COL;j++){  
                        printf("%2d ",maze->map[i][j]);  
                    }  
            printf("\n");  
        }  
    return;  
}  
  
int CanStay(Maze* maze,Point pt){//判断当前点是否能落脚  
    if(pt.row < 0 || pt.row >= MAX_ROW || pt.col < 0 || pt.col >= MAX_COL){  
            return 0;  
        }  
    int value = maze->map[pt.row][pt.col];  
    if(value == 1){  
            return 1;  
        }  
    return 0;  
}  
  
void Mark(Maze* maze,Point cur){//标记走过的路径  
    maze->map[cur.row][cur.col] = 2;  
}  
  
int IsExit(Maze* maze,Point cur,Point entry){  
    (void)maze;  
    //1.判断当前点是不是入口，若为入口，则不是出口  
    if(cur.row == entry.row && cur.col == entry.col){  
            return 0;  
        }  
        //2.如果当前点在地图边界上，说明是出口  
        if(cur.row == 0 || cur.row == MAX_ROW-1 || cur.col == 0 || cur.col == MAX_COL-1){  
                return 1;  
            }  
            return 0;  

}  
  
void GetPathByLoop(Maze* maze,Point entry){  
    if(maze == NULL)  
        return;  
    //1.创建一个栈，并且初始化，这个栈保存着走过的路径  
     SeqStack stack;  
     SeqStackInit(&stack);  
    //2.判定入口点能否落脚，若不能，说明参数非法,则直接返回 
     if(!CanStay(maze,entry)){  
             return;  
         }      
    //3.标记入口点，并将入口点入栈
    Mark(maze,entry);  
    SeqStackPush(&stack,entry);  
    //4.进入循环，获取到当前栈的栈顶元素
    Point cur;  
    while(GetTop(&stack,&cur)){  
        //5.判定这个点是否为出口，若为出口，直接函数返回  
        if(IsExit(maze,cur,entry)){  
                    printf("找到了一条路径\n");  
                    return;  
                }  
            //6.按照顺时针方向取相邻点，判断相邻点能否落脚，若能落脚，就标记并入栈，立即进入下一轮循环
            Point up = cur;  
                up.row -= 1;  
                    if(CanStay(maze,up)){  
                            Mark(maze,up);  
                            SeqStackPush(&stack,up);  
                            continue;  
                        }  
                      
                        Point right = cur;  
                            right.col += 1;  
                                if(CanStay(maze,right)){  
                                        Mark(maze,right);  
                                        SeqStackPush(&stack,right);  
                                        continue;  
                                    }  
                                  
                                    Point down = cur;  
                                        down.row += 1;  
                                            if(CanStay(maze,down)){  
                                                    Mark(maze,down);  
                                                    SeqStackPush(&stack,down);  
                                                    continue;  
                                                }  
                                              
                                                Point left = cur;  
                                                    left.col -= 1;  
                                                        if(CanStay(maze,left)){  
                                                                Mark(maze,left);  
                                                                SeqStackPush(&stack,left);  
                                                                continue;  
                                                            }  
                                                            //7.若四个相邻点均不能落脚，就出栈当前点，相当于进行回溯 
                                                            SeqStackPop(&stack);  
                                                                }  
        return;  
}
