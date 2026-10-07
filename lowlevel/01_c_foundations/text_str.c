

#include <stdio.h>
#include <stdlib.h>


char *my_strcpy(char *dst, const char *src){
    char *start = dst;
    for( ; *src; src++, dst++){
        *dst = *src;
    }
    *dst = '\0';
    return start;
}

int main(){
    char **str_arr;
    str_arr = malloc(sizeof(*str_arr)*4);
    str_arr[0] = malloc(sizeof(char)*16);
    str_arr[1] = malloc(sizeof(char)*16);
    str_arr[2] = malloc(sizeof(char)*16);
    str_arr[3] = malloc(sizeof(char)*16);
    
    my_strcpy(str_arr[0], "hi");
    my_strcpy(str_arr[1], "by");
    my_strcpy(str_arr[3], "my");
    str_arr[3] = NULL;

    for(int i = 0; i < 4; i++){
        printf("string: %s\n", str_arr[i]);
    }
}
