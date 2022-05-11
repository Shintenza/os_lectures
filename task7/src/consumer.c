#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "include/mem_handlers.h"
#include "include/sem_handlers.h"

int main (int argc, char** argv) {
    /*sprawdzenie podanej liczby argumentów*/
    if (argc < 5) {
        fprintf(stderr, "Niepoprawna składnia polecenia. Argumenty: [producer semaphore], [consumer semaphore], [shared memory], [output file]");
        exit(1);
    }
    /*otwieranie semaforów/pamięci dzielonej*/
    sem_t* prod_sem = semaphore_open(argv[1]);
    sem_t* cons_sem = semaphore_open(argv[2]);
    int shm_des = mem_open(argv[3]);
    int output = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);

    SegWrapper* smp = mem_map(shm_des, sizeof(SegWrapper));
    
    printf("[CONSUMER::INFO] >> NAZWA SEMAFORA: %s >> ADRES: %p\n", argv[1], (void*) prod_sem);
    printf("[CONSUMER::INFO] >> NAZWA SEMAFORA: %s >> ADRES: %p\n\n", argv[2], (void*) cons_sem);

    /*główna pętla konsumenta*/
    while (1) {
        semaphore_wait(cons_sem);
        if (smp->end_mark > 0 && (smp->buffer[smp->out_index][smp->end_mark] == '\0')) {
            printf("[CONSUMER] >> WIELKOŚĆ DANYCH: %d >> BUFF INDEX: %d >> P_SEM: %d >> K_SEM: %d >> %.*s\n",
                smp->end_mark, smp->out_index, semaphore_get_value(prod_sem), semaphore_get_value(cons_sem), smp->end_mark, smp->buffer[smp->out_index]);
            if (write(output, smp->buffer[smp->out_index], smp->end_mark) == -1 ) {
                perror("write error");
                exit(1);
            }
            break;
        } else {
            printf("[CONSUMER] >> WIELKOŚĆ DANYCH: %d >> BUFF INDEX: %d >> P_SEM: %d >> K_SEM: %d >> %.*s\n",
                N_ELE, smp->out_index, semaphore_get_value(prod_sem), semaphore_get_value(cons_sem), N_ELE, smp->buffer[smp->out_index]);
            if (write(output, smp->buffer[smp->out_index], N_ELE) == -1 ) {
                perror("write error");
                exit(1);
            }
            smp->out_index = (smp->out_index + 1) % N_BUF;
            semaphore_post(prod_sem);
        }
    }

    if (close(output) == -1 ) {
        perror("nie udało się zamknąć pliku wyjściowego");
        exit(1);
    }
    semaphore_close(prod_sem);
    semaphore_close(cons_sem);
    mem_unlink(smp, sizeof(SegWrapper));
    mem_close(shm_des);

    return 0;
}
