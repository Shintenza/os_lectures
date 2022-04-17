#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

#define FIFO_NAME "fifo"
#define PRODUCER "producer"
#define CONSUMER "consumer"

void signal_handler () {
    if(unlink(FIFO_NAME) == 0) {
        printf("Usunięto potok!\n");
        _exit(0);
    } else {
        fprintf(stderr, "Nie usunięto potoku!\n");
        _exit(1);
    }
}
void exit_handler () {
    if(unlink(FIFO_NAME) == 0) {
        printf("Pomyślnie usunięto potok!\n");
    } else {
        fprintf(stderr, "Nie usunięto potoku!\n");
    }
}
int main(int argc, char** argv) {
    int i;
    if (atexit(signal_handler)!=0) {
        perror("atexit error\n");
        exit(1);
    }

    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal error");
        exit(1);
    }
    if (argc < 2) {
        fprintf(stderr, "Niepoprawna ilość argumentów! Składnia ./handler [in] [out]\n");
        exit(1);
    }
    mkfifo(FIFO_NAME, 0644);
    for (i = 0; i < 2; i++) {
        switch(fork()) {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                if (i==1) {
                    if (execlp("./bin/"PRODUCER, PRODUCER, FIFO_NAME, argv[1]) == -1) {
                        perror("exec error");
                        exit(1);
                    }
                    break;
                } else {
                    if (execlp("./bin/"CONSUMER, CONSUMER, FIFO_NAME, argv[2]) == -1) {
                        perror("exec error");
                        exit(1);
                    }
                }
            default:
                break;
        }

    }
    for (i = 0; i< 2; i++) {
        wait(NULL);
    }
    return 0;    
}
