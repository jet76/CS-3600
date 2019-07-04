#define _GNU_SOURCE // https://github.com/Microsoft/vscode/issues/71012
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    pid_t child;
    assert((child = getpid()) >= 0);
    while(1){ // https://stackoverflow.com/questions/30678905/what-is-the-proper-equivalent-of-whiletrue-in-plain-c
        assert(printf("Awake in %d\n", child) != 0);
        sleep(1);
    }
    return 0;
}