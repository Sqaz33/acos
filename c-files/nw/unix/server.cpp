#include <iostream>
#include <string_view>
#include <memory>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

auto sp = "/tmp/mysocket1";


int main() {
    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) return 1;

    sockaddr_un myAddr;
    memset(&myAddr, 0, sizeof(myAddr));
    myAddr.sun_family = AF_UNIX;
    strcpy(myAddr.sun_path, sp);
    if (bind(sfd, (sockaddr*)(&myAddr), sizeof(myAddr)) == -1) {
        close(sfd);
        unlink(sp);
        return 1;
    }

    
    if (listen(sfd, 128) == -1) {
        close(sfd);
        unlink(sp);
        return 1;        
    }

    while (true) {
        sockaddr_un peerAddr;
        socklen_t perrAddrLen;
        int cfd = accept(sfd, (sockaddr*)(&peerAddr), 
                            &perrAddrLen);
        if (cfd == -1) {
            close(sfd);
            unlink(sp);
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
    unlink(sp);
    return 0;

}