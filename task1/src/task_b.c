#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main () {
    int i; 

    pid_t pgid = getpgid(0);
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), pgid);

    for (i=0; i<3; i++) {
        switch(fork()) {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                pgid = getpgid(0);
                printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), pgid);
            default:
                wait(NULL);
        }
    }
    return 0;
}
