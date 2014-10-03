#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

u_short portbase = 0;

int passivesock(const char *service, const char *transport, int qlen) {
    struct servent *pse;
    struct protoent *ppe;
    struct sockaddr_in sin;
    int s, type;

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    if (pse = getservbyname(service, transport)) {
        sin.sin_port = htons(ntohs((u_short) pse->s_port) + portbase);
        sin.sin_port = 2333;
    } else if ((sin.sin_port = htons((u_short) atoi(service))) == 0)
        perror("can't get service entry\n");
    memset(&sin.sin_zero, 0, sizeof(sin.sin_zero));

    /* Map protocol name to protocol number */
    if((ppe = getprotobyname(transport)) == 0)
        perror("can't get protocol entry\n");
    /* Use protocol to choose a socket type */
    if(strcmp(transport, "udp") == 0)
        type = SOCK_DGRAM;
    else
        type = SOCK_STREAM;
    /* Allocate a socket */
    s = socket(PF_INET, type, ppe->p_proto);
    if (s < 0)
        perror("can't create socket\n");
    /* Bind the socket */
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        printf("can't bind to %s port %d: %s\n", service, sin.sin_port, strerror(errno));
        perror("can't bind to %s port: %s\n");
    }
    if (type == SOCK_STREAM && listen(s, qlen) < 0)
        perror("can't listen on %s port: %s\n");
    return s;
}

int passiveUDP(const char *service) {
    return passivesock(service, "udp", 0);
}

int passiveTCP(const char *service, int qlen) {
    return passivesock(service, "tcp", qlen);
}

void TCPdaytimed(int fd) {
    char *pts;
    time_t now;
    char *ctime();
    time(&now);
    pts = ctime(&now);
    write(fd, pts, strlen(pts));
}

int main() {
    struct sockaddr_in fsin;
    char *service = "daytime";
    int msock, ssock;
    int alen;
    msock = passiveTCP(service, 5);
    while (1) {
        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
        if (ssock < 0)
            perror("accept failed\n");
        TCPdaytimed(ssock);
        close(ssock);
    }

    return 0;
}
