#include <stddef.h>
#include <stdio.h>


size_t my_strlen(const char *str);
char *my_strcpy(char *dst, const char *src);
char *my_strcat(char *dst, const char *src);

int main(){
    const char* h = "some";
    printf("len is: %ld\n", my_strlen(h));
}




size_t my_strlen(const char *str){
    const char *tmp;
    for(tmp = str; *tmp; tmp++);
    return tmp - str;
}


