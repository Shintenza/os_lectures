#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/*Kamil Kuziora 17.03.2022 Kraków*/
/*Program mający na celu tworzenie procesow adoptowanych przez systemd*/

void print_ids () {
    pid_t pgid = getpgid(0);
    if (pgid == -1)  {
        perror("could't get pgid!\n");
    }
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), pgid);
}

int main () {
    int i; 

    print_ids();
    for (i=0; i<3; i++) {
        switch(fork()) {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                sleep(10);
                print_ids();
                break;
            default:
                break;
        }
    }
    return 0;
}
