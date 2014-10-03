#ifndef _SOCK_UTIL
#define _SOCK_UTIL

int make_passive_socket_tcp(int port, int backlog);
int make_active_socket_tcp(const char *hostname, int port);
int init_sockaddr(struct sockaddr_in *addr, const char *hostname, uint16_t port);

#endif
