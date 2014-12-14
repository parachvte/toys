#include "BufferObj.h"
#include <fstream>


PBUFFER_OBJ GetBufferObj(PSOCKET_OBJ pSocket, ULONG nLen)
{
    PBUFFER_OBJ pBuffer = (PBUFFER_OBJ) ::GlobalAlloc(GPTR, sizeof(BUFFER_OBJ));
    if (pBuffer != NULL)
    {
        pBuffer->buff = (char *) ::GlobalAlloc(GPTR, nLen);
        pBuffer->nLen = nLen;
        pBuffer->ol.hEvent = ::WSACreateEvent();
        pBuffer->pSocket = pSocket;
    }
    return pBuffer;
}

void FreeBufferObj(PBUFFER_OBJ pBuffer)
{
    ::CloseHandle(pBuffer->ol.hEvent);
    ::GlobalFree(pBuffer->buff);
    ::GlobalFree(pBuffer);
}

BOOL PostRecv(PBUFFER_OBJ pBuffer)
{
    PSOCKET_OBJ pSocket = pBuffer->pSocket;
    pBuffer->nOperation = OP_READ;
    pSocket->nOutstandingOps ++;

    DWORD dwBytes;
    DWORD dwFlags = 0;
    WSABUF buf;
    buf.buf = pBuffer->buff;
    buf.len = pBuffer->nLen;
    if (::WSARecv(pSocket->s, &buf, 1, &dwBytes, &dwFlags, &pBuffer->ol, NULL)
            != NO_ERROR)
    {
        if (::WSAGetLastError() != WSA_IO_PENDING)
            return FALSE;
    }
    return TRUE;
}

BOOL PostSend(PBUFFER_OBJ pBuffer)
{
    PSOCKET_OBJ pSocket = pBuffer->pSocket;
    pBuffer->nOperation = OP_WRITE;
    pSocket->nOutstandingOps ++;

    DWORD dwBytes;
    DWORD dwFlags = 0;
    WSABUF buf;
    buf.buf = pBuffer->buff;
    buf.len = pBuffer->nLen;
    if (::WSASend(pSocket->s, &buf, 1, &dwBytes, dwFlags, &pBuffer->ol, NULL)
            != NO_ERROR)
    {
        if (::WSAGetLastError() != WSA_IO_PENDING)
            return FALSE;
    }
    return TRUE;
}

BOOL ReadFileToBuffer(PBUFFER_OBJ pBuffer)
{
    char file_name[100];
    if (pBuffer->nLen > 100)
        return FALSE;

    strncpy(file_name, pBuffer->buff, pBuffer->nLen);
    file_name[pBuffer->nLen] = '\0';

    std::ifstream is(file_name, std::ifstream::in);
    if (is)
    {
        is.seekg(0, std::ios::end);
        size_t size = is.tellg();
        if (size > BUFFER_SIZE)
            return FALSE;

        std::string buffer(size, ' ');
        is.seekg(0);
        is.read(&buffer[0], size);

        strncpy(pBuffer->buff, buffer.c_str(), size);
        pBuffer->nLen = size;
        return TRUE;
    } else
        return FALSE;
}
