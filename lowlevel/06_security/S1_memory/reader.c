#include <fcntl.h>      // open, O_RDONLY
#include <string.h>
#include <unistd.h>     // lseek, read, close
#include <stdlib.h>     // strtoull для парсинга адреса
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define BUF_SIZE 128

int main(int argc, char **argv){
    unsigned long long addr = strtoull(argv[2], NULL, 16);
    char *buffer = malloc(BUF_SIZE);

    char path[64];
    snprintf(path, sizeof(path), "/proc/%s/mem", argv[1]);
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "open %s: %s\n", path, strerror(errno));    
        return 1;
    }
    lseek(fd, (off_t)addr, SEEK_SET);
    ssize_t n = read(fd, buffer, BUF_SIZE - 1);   // -1: место под свой '\0'
    if (n == -1) {
        fprintf(stderr, "error %s: %s\n", buffer, strerror(errno));  
        return 1; 
    }
    buffer[n] = '\0';   
    

    printf("Info at adress: %s\n", buffer);
    return 0;
}
