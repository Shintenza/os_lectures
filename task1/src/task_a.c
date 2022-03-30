#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/*Kamil Kuziora 17.03.2022*/

/*Program wypisujacy identyfikatory UID, GID, PID, PPID i PGID*/

int main () {
    pid_t pgid = getpgid(0);
    /*blad w wykonywaniu f. getpgid*/
    if (pgid == -1) {
        perror("could't get pgid!\n");
    }
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), pgid);
    return 0;
}
