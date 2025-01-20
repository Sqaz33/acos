#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <unistd.h>


volatile sig_atomic_t caught_signum = 0;

void handler(int signum) {
    caught_signum = signum;
}

int main() {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;

    sigaction(SIGINT, &act, NULL);

    while (1) {
        pause();
        printf("Got signal %d\n", caught_signum);
    }
}