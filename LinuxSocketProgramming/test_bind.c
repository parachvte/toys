#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MYPORT 2333

int main() {
    int sockfd;
    struct sockaddr_in my_addr;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket() error");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), 0, 8);

    // Once the service is down, we should wait for the port to clear,
    // or just call setsockopt() to reuse the port
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsocketopt() error");
        exit(1);
    }

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof (struct sockaddr)) == -1) {
        perror("bind() error");
        exit(1);
    }

    return 0;
}
