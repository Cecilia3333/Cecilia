#include <string.h>

char* mystrrstr(const char* s1,const char* s2){
    char* last;
    char* cur;
    last = NULL;
    if(*s2 != '\0'){
        cur = strstr(s1,s2);
    while(cur != NULL){
        last = cur;
        cur = strstr(last + 1,s2);
    }
    }
    return last;
}

int main(){
    char arr1[] = "one world,one dream";
    char arr2[] = "one";
    char* ret = mystrrstr(arr1,arr2);
    printf("%s\n",ret);
    return 0;
}
