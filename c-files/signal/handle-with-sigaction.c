#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>

void handler(int sigsum) {
    puts("Cntr c\n");
}

void handle_3_arg(int sigsum, siginfo_t* info, void* ctx) {
    printf("%d from %d\n", sigsum, info->si_pid);
}

int main() {
    struct sigaction int_handler;
    memset(&int_handler, 0, sizeof(int_handler));

    int_handler.sa_handler = handler;
    // int_handler.sa_flags = SA_RESTART;
    int_handler.sa_flags = SA_RESETHAND;
    sigaction(SIGINT, &int_handler, NULL);


    struct sigaction term_handler;
    memset(&term_handler, 0, sizeof(term_handler));

    term_handler.sa_sigaction = handle_3_arg;
    term_handler.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGTERM, &term_handler, NULL);

    while (1) sched_yield();
}