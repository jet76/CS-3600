#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int child = getpid();
    if(child < 0){
        perror("getpid error");
        exit(errno);
    }
    assert(printf("Child PID: %d\n", child) >= 0);
    int parent = getppid();
    if(parent < 0){
        perror("getppid error");
        exit(errno);
    }
    assert(printf("Parent PID: %d\n", parent) >= 0);
    long n = 0;
    if(argc > 1){
        char *endptr;
        n = strtol(argv[1], &endptr, 0);
        for(int i = 1; i <= n; i++){
            assert(printf("Process: %d %d\n", child, i) >= 0);
        }
    }
    return n;
}