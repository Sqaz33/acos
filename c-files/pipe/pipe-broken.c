#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void write_to_channel(int channel[2], const char *data) { 
    write(channel[1], data, strlen(data));
    close(channel[1]);
}

int main() { 
    int channel[2];  
    pipe(channel); 

    pid_t pid = fork();
    if (0 == pid) {
        // child process that will write to pipe
        close(channel[0]);
        write_to_channel(channel, "Hello");
        _exit(0);
    }

    // parent process that will read from pipe
    close(channel[0]); // !!!
    
    int st = 0;
    waitpid(pid, &st, 0);
    if (WIFEXITED(st)) {
        printf("Child exited with this code %d\n", WEXITSTATUS(st));
    } else if (WIFSIGNALED(st)) {
        printf("Child killed by signal %d\n", WTERMSIG(st)); // 13 - SIGPIPE
    }
} 