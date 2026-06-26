#include <stdio.h>

int add(int a, int b);
int multiple(int a, int b);
int minus(int a, int b);
void apply(int a, int b, int (*fp)(int, int));


int main(){
    int x = 2;
    int y = 3;
    int (*ops[3])(int,int) = {add, minus, multiple};
    
    for (int i = 0; i < 3; i++) {
        apply(x, y, ops[i]);
    }
    
}

void apply(int a, int b, int (*fp)(int, int)){
    printf("function : %d\n" , fp(a, b));
}

int add(int a, int b){
    return a+b;
}
int minus(int a, int b){
    return a-b;
}
int multiple(int a, int b){
    return a*b;
}


