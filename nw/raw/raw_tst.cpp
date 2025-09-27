#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

int main(int argc, char** argv) {
    if (2 != argc) {
        std::cerr << "Usage: ./programm <interface name>\n";
        return 1;
    }

    int sock = socket(AF_PACKET, 
                        SOCK_RAW, htons(ETH_P_ALL));
    if (-1 == sock) {
        perror("socket");
        return 1;
    }
    ifreq req;
    strcpy(req.ifr_ifrn.ifrn_name, argv[1]);
    ioctl(sock, SIOCGIFINDEX, &req, sizeof req);

    sockaddr_ll addr = {
        .sll_family   = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex  = req.ifr_ifindex
    };

    int bindRes = bind(sock, 
                        reinterpret_cast<sockaddr*>(&addr), 
                        sizeof addr);
    if (-1 == bindRes) {
        perror("socket");
        return 1; 
    }

    for (;;) {
        char buf[4096] = {};
        size_t cnt = recv(sock, buf, sizeof buf, 0);
        uint32_t from_ip, to_ip;
        memcpy(&from_ip, buf+26, sizeof from_ip);
        memcpy(&to_ip, buf+30, sizeof to_ip);

        char from_addr[20] = {};
        char to_addr[20] = {};
        inet_ntop(AF_INET, &from_ip, from_addr, sizeof(from_addr));
        inet_ntop(AF_INET, &to_ip, to_addr, sizeof(to_addr));

        std::cout << "Communication from: " 
                  << from_addr
                  << ", to "
                  << to_addr 
                  << "\n";

    }

    return 0;
}