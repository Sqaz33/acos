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


void write_to_channel(int channel[2], const char* str) {
    write(channel[1], str, strlen(str));
    close(channel[1]);
}

int main() {
    int channel[2];
    pipe(channel);

    pid_t child_1 = fork();
    if (0 == child_1) {
        write_to_channel(channel, "Hi from child_1");
        _exit(0);
    }

    pid_t child_2 = fork();
    if (0 == child_2) {
        write_to_channel(channel, "Hi from child_2");
        _exit(0);
    }

    close(channel[1]);

    read_from_channel(channel);
    wait(NULL);
    wait(NULL);
}