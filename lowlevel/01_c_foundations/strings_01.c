#include <stdio.h>

int my_strlen(const char *src){
    const char *tmp;
    for(tmp = src; *tmp; tmp++)
        {}
    return tmp - src;
}

int main(){
    const char *str = "somem";
    //fgets(str, N, stdin);

    printf("Output: %d\n", my_strlen(str));
}
