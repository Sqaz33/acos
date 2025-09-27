#include <iostream>
#include <string_view>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) return 1;

    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(7800);
    servAddr.sin_addr.s_addr = inet_addr("172.31.4.199");

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