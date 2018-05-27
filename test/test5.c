#include <stdio.h>  
#include<assert.h>  
#include<string.h>  
#include<ctype.h>

void Reverse(char *p,char* q){  
    int tmp = 0;  
    while(p < q){  
            tmp = *p;  
            *p = *q;  
            *q = tmp;  
            p++;  
            q--;  
        }  
}  
void str_reverse(char* str){  
    assert(str);  
    char* head = str;  
    char* tail = str;  
    while(*tail){  
            if(isspace(*tail)){  
                        Reverse(head,tail-1);  
                        tail++;  
                        head = tail;  
                    }  
            else  
                tail++;  
        }  
    Reverse(head,tail-1);  
    Reverse(str,tail-1);  
}  
int main(){  
    char arr[]="I like Beijing.";  
    str_reverse(arr);  
    printf("%s\n",arr);  
    return 0;  
}  
