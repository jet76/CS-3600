#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    assert(printf("Enter a number: ") > 0);
    int n;
    assert(scanf("%d", &n) > 0);
    int child = getpid(0);
    assert(printf("Child PID: %d\n", child) > 0);
    int parent = getppid(0);;
    assert(printf("Parent PID: %d\n", parent)> 0);
    for(int i = 1; i <= n; i++){
        child = getpid(n);
        assert(printf("Process: %d %d\n", child, i) > 0);
    }
    return 0;
}