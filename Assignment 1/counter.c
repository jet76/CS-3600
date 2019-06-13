#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    assert(printf("Child PID: %d\n", getpid()) != 0);
    assert(printf("Parent PID: %d\n", getppid()) != 0);
    int i = 0;
    if(argc == 2){
        char *endptr;
        long n = strtol(argv[1], &endptr, 0);
        for(i = 1; i <= n; i++){
            assert(printf("Process: %d %d\n", getpid(), i) != 0);
        }
    }
    return i;
}