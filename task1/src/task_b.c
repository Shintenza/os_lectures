#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/*Kamil Kuziora 17.03.2022*/
/*wywoływanie funkcji fork 3 razy; uzycie wait aby proces-rodzic zaczekal na proces potomny*/

int main () {
    int i; 

    pid_t pgid = getpgid(0);

    if (pgid == -1) {
        perror("could't get pgid!\n");
    }
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), pgid);

    for (i=0; i<3; i++) {
        switch(fork()) {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                pgid = getpgid(0);
                if (pgid == -1) {
                    perror("could't get pgid!\n");
                }
                printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), pgid);
            default:
                wait(NULL);
                break;
        }
    }
    return 0;
}
