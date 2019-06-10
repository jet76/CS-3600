#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    assert(printf("Child PID: %d\n", getpid()) != 0);
    assert(printf("Parent PID: %d\n", getppid()) != 0);
    long n = 0;
    if(argc > 1){
        char *endptr;
        n = strtol(argv[1], &endptr, 0);
        for(int i = 1; i <= n; i++){
            assert(printf("Process: %d %d\n", getpid(), i) != 0);
        }
    }
    return n;
}