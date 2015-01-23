#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>


int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("usage: %s <interface> [<interface> ..]\n", argv[0]);
        exit(1);
    }

    struct ifreq ifr;

    /* Assume that all args are interface names */
    const int N_INTERFACE = argc - 1;
    char **interface = argv + 1;


    /* IPv4 IP address */
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;

    /* I want IP address attached to `interface[i]` */
    for (int i = 0; i < N_INTERFACE; ++i) {
        strncpy(ifr.ifr_name, interface[i], IFNAMSIZ-1);

        ioctl(fd, SIOCGIFADDR, &ifr);

        const char *ip_str = inet_ntoa(
                ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

        /* If the interface's IP is not empty, print it and jump out */
        if (strncmp(ip_str, "0.0.0.0", 15)) {
            printf("%s\n", ip_str);
            break;
        }
    }

    close(fd);
    return 0;
}
