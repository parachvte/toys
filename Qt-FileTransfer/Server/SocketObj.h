#ifndef SOCKETOBJ_H
#define SOCKETOBJ_H

#include <winsock2.h>
#include <mswsock.h>

typedef struct _SOCKET_OBJ
{
    SOCKET s;
    int nOutstandingOps;
} SOCKET_OBJ, *PSOCKET_OBJ;

PSOCKET_OBJ GetSocketObj(SOCKET s);
void FreeSocketObj(PSOCKET_OBJ pSocket);
void CleanupSocket(PSOCKET_OBJ pSocket);

#endif // SOCKETOBJ_H
