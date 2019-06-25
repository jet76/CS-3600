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
#include <syscall.h>

void handler(int sig){
    
}

int main(){

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    assert(sigaction(SIGCHLD, &action, NULL) == 0);

    int status;
    pid_t f = fork();
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
        char stop[] = "Parent is going to SIGSTOP the child\n.";
        char start[] = "Parent is going to SIGCONT the child.\n";
        for(int i = 0; i < 5; i++){            
            syscall(write(1, stop, strlen(stop)));
            assert(kill(f, SIGSTOP) == 0);
            sleep(2);
            syscall(write(1, start, strlen(start)));
            assert(kill(f, SIGCONT) == 0);
            sleep(2);
        }
        assert(kill(f, SIGINT) == 0);
    }
    else{
        assert(waitpid(f, &status, 0) >= 0);
        if(WIFSIGNALED(status)){
            assert(printf("Process %d exited with status: %d\n", f, WEXITSTATUS(status)) != 0);
        }
    }
    return 0;
}