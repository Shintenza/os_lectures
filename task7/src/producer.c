#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <string.h>

#include "include/sem_handlers.h"
#include "include/mem_handlers.h"
/*arguments: producer semaphore, consumer semaphore, shared memory, input file*/

int main (int argc, char** argv) {
    if (argc < 5) {
        fprintf(stderr, "Niepoprawna składnia polecenia. Argumenty: [producer semaphore], [consumer semaphore], [shared memory], [input file]");
        exit(1);
    }

    sem_t *prod_sem = semaphore_open(argv[1]);
    sem_t *cons_sem = semaphore_open(argv[2]);

    int shm_des     = mem_open(argv[3]);
    int source = open(argv[4], O_RDONLY);
    int count;

    if (source == -1) {
        perror("nie udało się otworzyć pliku źródłowego");
        exit(1);
    }
    

    SegWrapper* shm = mem_map(shm_des, sizeof(SegWrapper));

    printf("[PRODUCER::INFO] >> NAZWA SEMAFORA: %s >> ADRES: %p\n", argv[1], (void*) prod_sem);
    printf("[PRODUCER::INFO] >> NAZWA SEMAFORA: %s >> ADRES: %p\n\n", argv[2], (void*) cons_sem);

    while (1) {
        semaphore_wait(prod_sem);
        count = read(source, shm->buffer[shm->in_index], N_ELE);
        
        if (count == -1) {
            perror("problem podczas odczytywania pliku źródła");
            exit(1);
        }

        if (count >= 0) {
            printf("[PRODUCER] >> WIELKOŚĆ DANYCH: %d >> BUFF INDEX: %d >> P_SEM: %d >> K_SEM: %d >> %.*s\n",
                count, shm->in_index, semaphore_get_value(prod_sem), semaphore_get_value(cons_sem), count, shm->buffer[shm->in_index]);
            if (count < N_ELE) {
                shm->end_mark = count;
                shm->buffer[shm->in_index][count] = '\0';
                semaphore_post(cons_sem);
                break;
            }
        }
        shm->in_index = (shm->in_index + 1) % N_BUF;
        semaphore_post(cons_sem);
    }
    /*zamknięcie semaforów i pamięci dzielonej*/
    semaphore_close(prod_sem);
    semaphore_close(cons_sem);
    mem_unlink(shm, sizeof(SegWrapper));
    mem_close(shm_des);

    return 0;
}
