/**
 * Results:
 * 1. New process starts execution by returning from fork().
 * 2. Child and parent are nearly identical.
 * 3. Parent gets the child process id from fork().
 * 4. Child gets 0 back from fork().
 * 5. Parent should wait for child to exit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    int i, pid;
    pid = fork();

    printf("Forking ... the pid: %d     (child pid)\n", pid);
    for (i = 0; i < 5; i++)
        printf(" %d     %d              (current pid)\n", i, getpid());

    if (pid)
        wait(NULL);

    return 0;
}

