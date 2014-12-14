#ifndef BUFFEROBJ_H
#define BUFFEROBJ_H

#include "SocketObj.h"

#define BUFFER_SIZE 65536

typedef struct _BUFFER_OBJ
{
    OVERLAPPED ol;
    char *buff;
    int nLen;
    PSOCKET_OBJ pSocket;
    sockaddr_in addrRemote;
    int nOperation;
#define OP_ACCEPT   1
#define OP_READ     2
#define OP_WRITE    3
    _BUFFER_OBJ *pNext;
} BUFFER_OBJ, *PBUFFER_OBJ;

PBUFFER_OBJ GetBufferObj(PSOCKET_OBJ pSocket, ULONG nLen);
void FreeBufferObj(PBUFFER_OBJ pBuffer);

BOOL PostRecv(PBUFFER_OBJ pBuffer);
BOOL PostSend(PBUFFER_OBJ pBuffer);
BOOL ReadFileToBuffer(PBUFFER_OBJ pBuffer);

#endif // BUFFEROBJ_H
