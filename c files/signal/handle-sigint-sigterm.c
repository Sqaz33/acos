#include <signal.h>
#include <sched.h>
#include <stdio.h>

int cflag = 1;

void handler(int signum) {
    // cflag = 0;
    printf("Caught signal %d\n", signum);
}

int main() {
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    while(cflag) sched_yield();
}