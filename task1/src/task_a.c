#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main () {
    pid_t pgid = getpgid(0);
    if (pgid == -1) {
        perror("could't get pgid!\n");
    }
    printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), pgid);
    return 0;
}
