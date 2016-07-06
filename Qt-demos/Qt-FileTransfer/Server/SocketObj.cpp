#include "SocketObj.h"


PSOCKET_OBJ GetSocketObj(SOCKET s)
{
    PSOCKET_OBJ pSocket = (PSOCKET_OBJ) ::GlobalAlloc(GPTR, sizeof(SOCKET_OBJ));
    if (pSocket != NULL)
        pSocket->s = s;
    return pSocket;
}

void FreeSocketObj(PSOCKET_OBJ pSocket)
{
    // If DO NOT want to close pSocket->s, please explicitly set pSocket->s
    // to INVALID_SOCKET
    if (pSocket->s != INVALID_SOCKET)
        ::closesocket(pSocket->s);
    ::GlobalFree(pSocket);
}

void CleanupSocket(PSOCKET_OBJ pSocket)
{
    // If error occurs on socket, then close it.
    // If there are no more unfinished I/Os on the socket, then free the
    // socket object. Otherwise wait for the unfinished I/Os to be completed.
    if (pSocket->s != INVALID_SOCKET)
    {
        ::closesocket(pSocket->s);
        pSocket->s = INVALID_SOCKET;
    }
    if (pSocket->nOutstandingOps == 0)
        FreeSocketObj(pSocket);
}
