#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    assert(kill(getppid(), SIGURG) == 0);
    assert(kill(getppid(), SIGUSR1) == 0);
    assert(kill(getppid(), SIGUSR2) == 0);
    return 0;
}