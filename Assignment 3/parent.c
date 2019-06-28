#define _GNU_SOURCE // https://github.com/Microsoft/vscode/issues/71012
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "syscall.h"

int status;
pid_t f;

int eye2eh(int i, char *buffer, int buffersize, int base);

void handler(int sig)
{
    if (WIFEXITED(status)){
        WRITESTRING("Process ");
        WRITEINT(f, 6);
        WRITESTRING(" exited with status: ");
        WRITEINT(WEXITSTATUS(status), 2);
        WRITESTRING("\n");
    }
    exit(0);
}

int main(){

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    assert(sigaction(SIGCHLD, &action, NULL) == 0);

    f = fork();
    if(f == -1){
        perror("fork error");
        exit(errno);
    }
    else if(f == 0){
        int n = execl("child", "child", NULL);
        if(n == -1){
            perror("execl error");
            exit(errno);
        }
    }
    else{
        assert(waitpid(f, &status, WNOHANG) >= 0);
        for (int i = 0; i < 5; i++)
        {
            assert(printf("Parent is going to SIGSTOP the child.\n") != 0);
            assert(kill(f, SIGSTOP) == 0);
            sleep(2);
            assert(printf("Parent is going to SIGCONT the child.\n") != 0);
            assert(kill(f, SIGCONT) == 0);
            sleep(2);
        }
        assert(kill(f, SIGINT) == 0);
        assert(pause() >= 0);
    }
    return 0;
}