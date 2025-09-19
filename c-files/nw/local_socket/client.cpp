#include <iostream>
#include <string_view>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

auto sp = "/tmp/mysocket1";

int main() {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1) return 1;

    sockaddr_un servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sun_family = AF_UNIX;
    strcpy(servAddr.sun_path, sp);
    
    int sfd = connect(sock, (sockaddr*)(&servAddr), 
                        sizeof(servAddr));
    if (-1 == sfd) {
        close(sock);
        return 1;
    }
    
    char msg[] = "Hi from client";
    
    write(sock, msg, sizeof msg);

    close(sock);
    return 0;

}