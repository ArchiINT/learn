#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data; //pointer for integer nums(arrays)
    size_t size; // actual size of array in bites
    size_t capazity; // max size for arrays
} Vector;

// create vector (calloc)
int vec_create(Vector *vec);
// add element and realloc if there is to low capazity
int vec_push(Vector *vec, int data);
// get element from index
int vec_get(Vector *vec, int index);
// free memory
int vec_free(Vector *vec);

int main() {
    Vector my_vector;
    vec_create(&my_vector);
    for(int i = 0; i < 20; i++){
        vec_push(&my_vector, i);
    }
    printf("Vector: %d\n",vec_get(&my_vector, 5));
    return 0;
}


int vec_create(Vector *vec){
    vec->data = calloc(4, sizeof(int)); // data get a memory (4 * int.bits) 4 int nums 
    if (vec->data == NULL) {
        return 1;
    }
    vec->capazity = sizeof(*vec->data);
    vec->size = 0;
    return 0;
}
int vec_push(Vector *vec, int data){
    if(vec->capazity == vec->size){
        int* tmp = realloc(vec->data, (sizeof(int) * 2 * vec->capazity));
        if(tmp == NULL){
            return 1;
        }
        vec->data = tmp;
        vec->capazity = vec->capazity * 2;
    }
    vec->data[vec->size] = data;
    vec->size++;
    printf("go throw size: %zu and %zu\n", vec->size, vec->capazity);
    return 0;
}
int vec_get(Vector *vec, int index){
    int *tmp = vec->data;
    if(index > vec->size){
        return 1;
    }
    int result = vec->data[index];
    vec->data = tmp;
    return result;
}
int vec_free(Vector *vec){
    free(vec->data);
    vec->data = NULL;
    return 0;
}

