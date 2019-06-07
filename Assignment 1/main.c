/* Help from Conor McCandless */
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t wait;
    pid_t f = fork();
    if(f == -1){
        perror("fork error");
        exit(errno);
    }
    else if(f == 0){
        int n = execl("counter", "5", NULL);
        if(n == -1){
            perror("execl error");
            exit(errno);
        }
    }
    else{
        wait = waitpid(f, &status, 0);
        if(wait == -1){
            perror("waitpid error");
            exit(errno);
        }  
        assert(printf("Process %d exited with status: %d\n", f, WEXITSTATUS(status)) > 0); 
    }
    return 0;
}