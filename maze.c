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
  
void MazePrint(Maze* maze){  
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
  
int CanStay(Maze* maze,Point pt){  
    if(pt.row < 0 || pt.row >= MAX_ROW || pt.col < 0 || pt.col >= MAX_COL){  
            return 0;  
        }  
    int value = maze->map[pt.row][pt.col];  
    if(value == 1){  
            return 1;  
        }  
    return 0;  
}  
  
void Mark(Maze* maze,Point cur){  
    maze->map[cur.row][cur.col] = 2;  
}  
  
nt IsExit(Maze* maze,Point cur,Point entry){  
    (void)maze;  
     if(cur.row == entry.row && cur.col == entry.col){  
             return 0;  
         }  
    if(cur.row == 0 || cur.row == MAX_ROW-1 || cur.col == 0 || cur.col == MAX_COL-1){  
            return 1;  
        }  
        return 0;  
}     

void _GetPath(Maze* maze,Point cur,Point entry){  
    printf("cur:(%d,%d)\n",cur.row,cur.col);  
    //1.判断当前点能否落脚  
     if(!CanStay(maze,cur)){  
             return;  
         }  
    //2.若能落脚，给当前位置做一个标记 
    Mark(maze,cur);  
        //3.若当前点为出口，说明找到了一条出口，探测结束  
    if(IsExit(maze,cur,entry)){  
        printf("找到了一条出路\n");  
        return;  
    }  
    //4.若当前点不是出口，则按顺时针方向探测四个相邻的点，递归式调用函数自身，递归式更新cur节点  
    //（每次递归时，cur都是下一次要走的点，这个点能否落脚，交给递归函数作判断）  
     Point up = cur;  
     up.row -= 1;  
     _GetPath(maze,up,entry);  
               
     Point right = cur;  
     right.col += 1;  
     _GetPath(maze,right,entry);  
                           
     Point down = cur;  
     down.row += 1;  
     _GetPath(maze,down,entry);  
                                       
     Point left = cur;  
     left.col -= 1;  
     _GetPath(maze,left,entry);  
}  
  
void GetPath(Maze* maze,Point entry){  
    if(maze == NULL){  
            return;  
        }  
    _GetPath(maze,entry,entry);  
}  
