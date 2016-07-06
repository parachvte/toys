#ifndef SOCKUTIL_H
#define SOCKUTIL_H

#include <QString>
#include <netinet/in.h>

class SockUtil
{
public:
    SockUtil();

    static int makeActiveTCP(const char *hostname, int port);
    static int makePassiveTCP(int port, int backlog);
private:
    static bool initSockaddr(struct sockaddr_in *addr, const char *hostname,
                            uint16_t port);
};

#endif // SOCKUTIL_H
