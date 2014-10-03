#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {
    struct hostent *hostinfo;
    hostinfo = gethostbyname("localhost");
    printf("%s\n", inet_ntoa(*(struct in_addr *)hostinfo->h_addr));

    hostinfo = gethostbyname("0.0.0.0");
    printf("%s\n", inet_ntoa(*(struct in_addr *)hostinfo->h_addr));
    return 0;
}
