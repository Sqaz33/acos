#include <stdio.h>
#include <string.h>
#include <unistd.h>


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

void write_to_channel(int channel[2], const char *data) { 
    write(channel[1], data, strlen(data));
    close(channel[1]);
}

int main() { 
    int channel[2];  
    pipe(channel); 

    // Try to change read/write order 
    write_to_channel(channel, "Hello"); 
    read_from_channel(channel);

    printf("%d - %d\n", channel[0], channel[1]);

    return 0;
} 