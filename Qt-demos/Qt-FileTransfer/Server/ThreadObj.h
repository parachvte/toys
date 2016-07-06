#ifndef THREADOBJ_H
#define THREADOBJ_H

#include "BufferObj.h"

typedef struct _THREAD_OBJ
{
    HANDLE events[WSA_MAXIMUM_WAIT_EVENTS];
    int nEventCount;
    int nBufferCount;
    PBUFFER_OBJ pBufferList;
    CRITICAL_SECTION cs;
    _THREAD_OBJ *pNext;
} THREAD_OBJ, *PTHREAD_OBJ;


// Thread itself
PTHREAD_OBJ GetThreadObj();
void FreeThreadObj(PTHREAD_OBJ pThread);

// Within Thread
// Rebuild mapping for BUFFER_OBJs and events
void RebuildEventArray(PTHREAD_OBJ pThread);

BOOL InsertBufferObj(PTHREAD_OBJ pThread, PBUFFER_OBJ pBuffer);
BOOL RemoveBufferObj(PTHREAD_OBJ pThread, PBUFFER_OBJ pBuffer);
PBUFFER_OBJ FindBufferObj(PTHREAD_OBJ pThread, HANDLE event);

BOOL HandleIO(PTHREAD_OBJ pThread, PBUFFER_OBJ pBuffer);
DWORD WINAPI WorkerThread(LPVOID lpParam);

// Thread List
extern CRITICAL_SECTION g_cs;
extern int g_nThreadCount;
BOOL AssignToFreeThread(PBUFFER_OBJ pBuffer);

#endif // THREADOBJ_H
