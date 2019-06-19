#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t parent;
    assert((parent = getppid()) >= 0);
    assert(kill(parent, SIGURG) == 0);
    assert(kill(parent, SIGURG) == 0);
    assert(kill(parent, SIGURG) == 0);
    assert(kill(parent, SIGUSR1) == 0);
    assert(kill(parent, SIGUSR2) == 0);
    return 0;
}