#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int child = getpid();
    assert(printf("Child PID: %d\n", child) > 0);
    int parent = getppid();
    assert(printf("Parent PID: %d\n", parent) > 0);
    long n = 0;
    if(argc > 0){
        char *endptr;
        n = strtol(argv[1], &endptr, 0);
        for(int i = 1; i <= n; i++){
            child = getpid();
            assert(printf("Process: %d %d\n", child, i) > 0);
        }
    }
    return n;
}