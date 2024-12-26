#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    pid_t pid = fork();
    if (0 == pid) {
        chdir("./c files");
        int fd = open("out.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
        dup2(fd, 1); close(fd);
        execlp("ls", "ls", "-l", NULL);
        perror("exec >~<\n");
        exit(2);
    } else {
        int* res = 0;
        waitpid(pid, res, 0);
    }
} 

