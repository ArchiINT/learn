

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 64

int main(){
    char *email_buf = malloc(BUF_SIZE);
    char *pass_buf = malloc(BUF_SIZE);

    if (email_buf == NULL || pass_buf == NULL) {
        return 1;
    }
    
    pid_t pid = getpid();
    printf("PID: %d\n", pid);

    printf("Print your Email: ");
    fgets(email_buf, BUF_SIZE, stdin);
    printf("Secret buffer at: %p\n", (void*)email_buf);
    // Here we start our attack programm
    printf("Print your Password: ");
    fgets(pass_buf, BUF_SIZE, stdin);

    free(email_buf);
    free(pass_buf);
}
