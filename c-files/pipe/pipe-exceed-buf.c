#include <stdio.h>
#include <unistd.h>


int main() {
    int channel[2] = {};
    pipe(channel);

    ssize_t count;
    size_t total = 0;
    while (1) {
        static const char eight_bytes[] = {0, 1, 2, 3, 4, 5, 6, 7};
        count = write(channel[1], eight_bytes, sizeof eight_bytes);
        total += 8;
        printf("Total bytes written: %zd\n", total);
    }
}