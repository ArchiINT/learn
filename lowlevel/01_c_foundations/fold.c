

#include <stdio.h>
int main(){
    const char *x = "hi";
    char *p = (char *)x;
    p[0] = 's';
    printf("x = %s, *p = %s\n", x, p);
    return 0;
}

