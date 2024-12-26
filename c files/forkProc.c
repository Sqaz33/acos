#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    pid_t res = fork();
    printf("PID: %d\n", res);
    if (res > 0) {
        int st = 0;
        waitpid(res, &st, 0);
        printf("Child exited with status: %d\n", st);
    }
    return res > 0 ? 0 : 1;
}
