#include "my_string.h"
#include <stdlib.h>

void free_split(char **list){
    if(list == NULL){
        return;
    }
    char **tmp = list;
    while(*tmp){
        free(*tmp);
        tmp++;
    }
    free(list);
}

size_t my_strlen(const char *str){
    const char *tmp;
    for(tmp = str; *tmp; tmp++);
    return tmp - str;
}


char *my_strcpy(char *dst, const char *src){
    char *start = dst;
    for( ; *src; src++, dst++){
        *dst = *src;
    }
    *dst = '\0';
    return start;
}


char *my_strcat(char *dst, const char *src){
    char *start = dst;
    for(; *dst; dst++);
    for(; *src; dst++, src++){
        *dst = *src;
    }
    *dst = '\0';
    return start;
}


char **my_strsplit(const char *str, char delim, size_t *count){
    const char *tmp = str;
    char **result;
    // Calculate how much tokens there is.
    size_t tokens = 1; 
    for(; *tmp; tmp++){
        if(*tmp == delim)
            tokens++;
    }
    // Create dinamyc mamory for array of pointers.
    result = malloc(sizeof(*result)*(tokens + 1));
    if(result == NULL){
        return NULL;
    }

    size_t i = 0; // Variable for each token;
    tmp = str; // Return pointer to start.
    const char *start = tmp;
    for(;; tmp++){ 
        //Go throw text until we meet a delim
        if(*tmp == delim || !*tmp){
            // Calculate how much symbols we have
            size_t len = tmp - start;
            // Memory for Object
            result[i] = malloc(sizeof(**result)*(len+1));
            // Memory Error
            if (result[i] == NULL) {
                while (i != 0){
                    i--;
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            // Copy symbols
            //
            for(size_t copy_count = 0; copy_count < len; copy_count++, start++){
                result[i][copy_count] = *start;
            }
            start++;
            result[i][len] = '\0';
            i++;
        }
        if(!*tmp){
            result[tokens] = NULL;
            *count = tokens;
            break;
        }
    }


    return result;
}
