#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

unsigned random_gen(int down, int up) {
    return (rand() % (up - down + 1)) + down;
}

int main () {
    int filedes[2];
    int source  = open("./payload.txt", O_RDONLY);
    int out     = open("./output.txt", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);


    char buffer[PIPE_BUF] = {0};
    char out_msg[PIPE_BUF + 69];
    unsigned size;
    unsigned count;
    int i =0;

    if (pipe(filedes) == -1) {
        perror("Pipe error");
        exit(1);
    }

    switch (fork()) {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            if (close(filedes[0]) == -1) {
                perror("close error");
                exit(1);
            }
            do {
                size = (rand() % (100 - 10 + 1)) + 10;
                count = read(source, buffer, size);
                if (count == -1) {
                    perror("read error");
                    exit(1);
                }
                buffer[count] ='\0';
                sprintf(out_msg, "[PRODUCENT] - %s\n", buffer);
                sleep(random_gen(0, 3));

                if (write(2, out_msg, strlen(out_msg)) == -1 || write(filedes[1], buffer, count) == -1 ) {
                    perror("write error");
                    exit(1);
                }
            } while (count > 0);

            if (close(filedes[1]) == -1) {
                perror("close error");
                exit(1);
            }
            break;
        default:
            if (close(filedes[1]) == -1) {
                perror("close error");
                exit(1);
            }
            while ((count = read(filedes[0], buffer, PIPE_BUF) ) > 0) {
                
                if (write(out, buffer, count) == -1) {
                    perror("parent write error");
                    exit(1);
                }
                buffer[count] = '\0';
                sprintf(out_msg, "[KONSUMENT] - %s\n", buffer);

                if (write(2, out_msg, strlen(out_msg)) == -1) {
                    perror("parent write error");
                    exit(1);
                }
            }
            if (count == -1) {
                perror("read error");
                exit(1);
            }
            if (close(filedes[0]) == -1) {
                perror("close error");
                exit(1);
            }
            break;
    }
}
