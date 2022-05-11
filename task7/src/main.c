#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <wait.h>

#include "include/mem_handlers.h"
#include "include/sem_handlers.h"

#define PRODUCER_SEM_NAME "/producer"
#define CONSUMER_SEM_NAME "/consumer"
#define SM_NAME "/sm"
#define PRODUCER "producer"
#define CONSUMER "consumer"
#define INPUT "payload.txt"
#define OUTPUT "output.txt"

/*własna funkcja wyjścia*/
void exit_fn() {
    semaphore_delete(PRODUCER_SEM_NAME);
    semaphore_delete(CONSUMER_SEM_NAME);
    mem_destroy(SM_NAME);
}
/*obsługa sygnału SIGINT*/
void sig_handler() {
    exit_fn();
    _exit(1);
}

int main (int argc, char **argv) {
    /*stworzenie semaforów*/
    sem_t* prod_sem = semaphore_create(PRODUCER_SEM_NAME, N_BUF);
    printf("[MAIN::INFO] >> utworzono semafor producenta >> NAZWA: %s >> ADRES: %p >> WARTOŚĆ: %d\n", PRODUCER_SEM_NAME, (void*) prod_sem, semaphore_get_value(prod_sem));
    sem_t* cons_sem = semaphore_create(CONSUMER_SEM_NAME, 0);
    printf("[MAIN::INFO] >> utworzono semafor konsumenta >> NAZWA: %s >> ADRES: %p >> WARTOŚĆ: %d\n\n", CONSUMER_SEM_NAME, (void*) cons_sem, semaphore_get_value(cons_sem));

    int i;

    /*desktryptor pamięci dzielonej*/
    int fd; 
    
    /*rejestrowanie funkcji wyjścia i obsługi sygnału SIGINT*/
    if (atexit(exit_fn) != 0) {
        perror("atexit error");
        exit(1);
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("signal error");
        exit(1);
    }
    
    /*tworzenie pamięci dzielonej*/
    fd = mem_create(SM_NAME, sizeof(SegWrapper));
    printf("[MAIN::INFO] >> utworzono pamięć dzieloną >> DES: %d >> ROZMIAR: %lu\n", fd, sizeof(SegWrapper));

    /*mapoanie i ustawienia początkowych wartości pamięci dzielonej*/
    SegWrapper *smp = (SegWrapper *) mem_map(fd, sizeof(SegWrapper));
    smp->in_index = 0;
    smp->out_index = 0;
    smp->end_mark = -1;
   
    /*tworzenie procesów potomnych*/
    for (i = 0; i < 2; i++) {
        switch(fork()) {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                if (i ==0 ) {
                    /*proces konsument*/
                    if (execlp("./bin/"CONSUMER, CONSUMER, PRODUCER_SEM_NAME, CONSUMER_SEM_NAME, SM_NAME, OUTPUT, NULL) == -1) {
                        perror("exec error");
                        _exit(1);
                    }
                } else {
                    /*proces producent*/
                    if (execlp("./bin/"PRODUCER, PRODUCER, PRODUCER_SEM_NAME, CONSUMER_SEM_NAME, SM_NAME, INPUT, NULL) == -1) {
                        perror("exec error");
                        _exit(1);
                    }
                }
            default:
                break;
        }
    }
    /*oczekiwanie na procesy potomne*/
    for (i = 0; i < 2; i++) {
        if (wait(NULL)==-1) {
            perror("wait error");
            exit(1);
        }
    }
    /*zamknięcie pamięci dzielonej i semaforów*/
    semaphore_close(prod_sem);
    semaphore_close(cons_sem);
    mem_close(fd);
    mem_unlink(smp, sizeof(SegWrapper));

    return 0;
}
