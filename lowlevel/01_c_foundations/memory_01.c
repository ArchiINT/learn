#include <stdio.h>
#include <stdlib.h>

int main(){
    int *arr = malloc(sizeof(int) * 5);
    int *start = arr;
    
    if (arr == NULL) {
        return 1;
    }
    
    for(int i = 1; i < 6; i++){
        *arr = i*10;
        arr++;
    }
    
    arr = start;

    for(int i = 0; i < 5; i++){
        printf("arr[%d]: %d\n", i, *arr);
        arr++;
    }

 //   free(start);
}
