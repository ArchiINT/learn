
#include <stdio.h>
#include <stdlib.h>
struct item{
    int data;
    struct item *next; 
};

int main(){
    struct item *first = NULL, *tmp, *next = NULL;
    for(int i = 0; i < 5; i++){
        tmp = malloc(sizeof(struct item));
        if (tmp == NULL) {
            return 1;
        }
        tmp->data = i;
        tmp->next = first;
        first = tmp;
    }

    for (tmp = first; tmp; tmp = tmp->next) {
        printf("%d\n",tmp->data);
    }

    // Free memory
    //
    tmp = first;
    while(tmp){
        next = tmp->next;
        free(tmp);
        tmp = next;
    }



}
