#include <iostream>
#include <string_view>
#include <memory>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


int main() {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) return 1;

    sockaddr_in myAddr;
    memset(&myAddr, 0, sizeof(myAddr));
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = htons(7800);
    myAddr.sin_addr.s_addr = inet_addr("172.31.4.199");
    if (bind(sfd, (sockaddr*)(&myAddr), sizeof(myAddr)) == -1) {
        close(sfd);
        return 1;
    }

    
    if (listen(sfd, 128) == -1) {
        close(sfd);
        return 1;        
    }

    while (true) {
        sockaddr peerAddr;
        socklen_t perrAddrLen;
        int cfd = accept(sfd, (sockaddr*)(&peerAddr), 
                            &perrAddrLen);
        if (cfd == -1) {
            close(sfd);
            return 1;
        }

        ssize_t count;
        char buf[4096] = {};
        for (;;) {
            count = read(cfd, buf, sizeof buf);
            if (count <= 0) break;
            std::string_view sv(buf, count);
            std::cout << "Client message: " << sv << '\n';
        }
        close (cfd);
    }

    close(sfd);
    return 0;

}