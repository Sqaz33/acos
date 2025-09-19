#include <sys/types.h>
#include <stdio.h>
#include <unistd.h> // файл с объявлениями системных вызовов

void main() {
    printf("abrakadabra ");
    // fflush(stdout);
    pid_t res = fork();
    printf("hi from: %d\n", res);
}