
#include <stddef.h>
#include <stdio.h>
int count_byte(const unsigned char *buf, size_t len, unsigned char target);

int main(void){
    unsigned char buffer[4096];
    int result = 0;
    size_t n = 0;
    while ((n = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        result += count_byte(buffer, n, '1');
    }
    printf("output: %d\n", result);
    return 0;
}


int count_byte(const unsigned char *buf, size_t len, unsigned char target){
    
    int count = 0;
    for(size_t i = 0; i < len; i++){
        if(buf[i] == target){
            count++;
        }
    }
    return count;
}

