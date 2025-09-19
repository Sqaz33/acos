#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int channel[2];
    pipe(channel);

    // setup channel[1] fd to non-blocking mode
    int old_flags = fcntl(channel[1], F_GETFL);
    int new_flags = old_flags | O_NONBLOCK;
    fcntl(channel[1], F_SETFL, new_flags);

    size_t bytes_total = 0;
    ssize_t count = 0;

    while (1) {
        static const char eight_bytes[] = {0, 1, 2, 3, 4, 5, 6, 7};
        count = write(channel[1], eight_bytes, sizeof eight_bytes);
        if (count >= 0) {
            bytes_total += count;
            printf("Total bytes written: %zd\n", bytes_total);
        } else if (-1 == count && EAGAIN == errno) {
            // flush pipe buffer by reading
            char read_buffer[65536];
            read(channel[0], read_buffer, sizeof read_buffer);
            puts("Flushed pipe buffer, will continue in 3 seconds");
            sleep(3);
        }
    }
}

/*
    errno — это глобальная переменная в языке программирования C, которая
    используется для хранения кода последней ошибки, возникшей в системных вызовах
    или функциях стандартной библиотеки.
*/