
#include <stdio.h>
int main(){
    int x = 42;
    int * p = &x;
    int **pp = &p;
    printf("x: %p\np: %p\npp: %p\n", &x,&p, &pp);


    printf("x: %d\np: %d\npp: %d\n", x, *p, **pp);

    **pp= 99;
    printf("x: %d\n", x);

    printf("sizeof(int)  = %zu\n", sizeof(int));
    printf("sizeof(int*) = %zu\n", sizeof(int*));
    printf("sizeof(int**) = %zu\n", sizeof(int**));
}
