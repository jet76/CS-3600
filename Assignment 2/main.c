#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int sig){
    switch(sig){
        case SIGURG:
            assert(printf("Received SIGURG (%d)\n", sig) != 0);
            break;
        case SIGUSR1:
            assert(printf("Received SIGUSR1 (%d)\n", sig) != 0);
            break;
        case SIGUSR2:
            assert(printf("Received SIGUSR2 (%d)\n", sig) != 0);
            break;
    }
}

int main(){

    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    assert(sigaction(SIGUSR1, &action, NULL) == 0);
    assert(sigaction(SIGUSR2, &action, NULL) == 0);
    assert(sigaction(SIGURG, &action, NULL) == 0);

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
    }
    else{
        assert(waitpid(f, &status, 0) >= 0);
        if(WIFEXITED(status)){
            assert(printf("\nProcess %d exited with status: %d\n", f, WEXITSTATUS(status)) != 0); 
        }
    }
    return 0;
}