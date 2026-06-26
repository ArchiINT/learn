
#include <stdio.h>
int main(){
    int x = 42;
    int *p = &x;
    *p = 100;
    printf("%d\n", x);
    printf("pointer: %p\n", p);
    printf("*p: %d\n", *p);

    return 0;
}