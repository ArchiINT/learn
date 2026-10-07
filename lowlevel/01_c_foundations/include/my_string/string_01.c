#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(){
    //const char* h = "some";
    //const char* shit = " shit";
    //char *copy = malloc(my_strlen(h)+my_strlen(shit)+1);
    //if(copy == NULL){
    //    return 1;
    //}
    //printf("len is: %zu\n", my_strlen(h));

    //my_strcpy(copy, h);
    //printf("%s\n", copy);
    //my_strcat(copy, shit);
    //printf("%s\n", copy);
    //free(copy);
    const char *my_str = "Hi, how, are, you, a,b";
    char **str_list;
    size_t list_count;
    str_list = my_strsplit(my_str, ',', &list_count);
    if(str_list == NULL ){
        fprintf(stderr, "my_strsplit: out of memory\n");
    }

    for(size_t i = 0; i<list_count; i++){
        printf("Each string: %s\n", str_list[i]);
    }

    //while (list_count != 0){
    //    list_count--;
    //    free(str_list[list_count]);
    //}
    //free(str_list);
    free_split(str_list);
    return 0;
}

