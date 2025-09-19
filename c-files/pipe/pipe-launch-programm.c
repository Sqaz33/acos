#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void read_from_channel(int channel[2]) {
    char buffer[4096] = {};
    ssize_t count = 0;
    while (1)  {
        count = read(channel[0], buffer, sizeof buffer);
        if (count <= 0) {
            puts("No more data in channel");
            break;
        }
        printf("Got %zd bytes from pipe: %s\n", count, buffer);
    }
}

int main() {
    int channel[2];  
    pipe(channel); 

    pid_t pid = fork();
    if (0 == pid) {
        close(channel[0]);
        dup2(channel[1], 1);
        execlp("ls", "ls", NULL);
        _exit(1);
    }

    close(channel[1]);
    read_from_channel(channel);
    wait(NULL);
}