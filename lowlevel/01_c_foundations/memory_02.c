#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_VECTOR_LENG 4

typedef struct {
    int *data; //pointer for integer nums(arrays)
    size_t size; // actual size of array in bites
    size_t capacity; // max size for arrays
} Vector;

// create vector (calloc)
int vec_create(Vector *vec);
// add element and realloc if there is to low capacity
int vec_push(Vector *vec, int data);
// get element from index
int vec_get(Vector *vec, int index);
// free memory
int vec_free(Vector *vec);

int main() {
    Vector my_vector;
    vec_create(&my_vector);
    for(int i = 0; i < 10; i++){
        vec_push(&my_vector, i);
    }
    printf("Vector: %d\n",vec_get(&my_vector, 5));
    vec_free(&my_vector);
    return 0;
}

int vec_create(Vector *vec){
    vec->data = calloc(INIT_VECTOR_LENG, sizeof(int)); // data get a memory (4 * int.bits) 4 int nums 
    if (vec->data == NULL) {
        return 1;
    }
    vec->capacity = INIT_VECTOR_LENG; // capacity == data.lenght bits. * used because without * we get size of pointer
    vec->size = 0;
    return 0;
}
int vec_push(Vector *vec, int data){
    if(vec->capacity == vec->size){
        int* tmp = realloc(vec->data, (sizeof(int) * 2 * vec->capacity));
        if(tmp == NULL){
            return 1;
        }
        vec->data = tmp;
        vec->capacity = vec->capacity * 2;
    }
    vec->data[vec->size] = data;
    vec->size++;
    printf("go throw size: %zu and %zu\n", vec->size, vec->capacity);
    return 0;
}
int vec_get(Vector *vec, int index){
    if(index >= vec->size){
        return 1;
    }
    int result = vec->data[index];
    return result;
}
int vec_free(Vector *vec){
    free(vec->data);
    vec->data = NULL;
    return 0;
}

