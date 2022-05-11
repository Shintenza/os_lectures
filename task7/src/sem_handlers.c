#include "include/sem_handlers.h"

/*tworzenie semafora*/
sem_t* semaphore_create(const char* semaphore_name, int value) {
    sem_t* sem =sem_open(semaphore_name, O_CREAT | O_EXCL, 0644, value);
    if (sem == SEM_FAILED) {
        perror("nie udało się utworzyć semafora\n");
        exit(1);
    }
    return sem;
}
/*otwieranie istniejącego semafora*/
sem_t* semaphore_open(const char* semaphore_name) {
    sem_t* sem = sem_open(semaphore_name, 0);
    if (sem == SEM_FAILED) {
        perror("nie udało się utworzyć semafora\n");
        exit(1);
    }
    return sem;
}
/*usuwanie semafora*/
void semaphore_delete(const char* semaphore_name) {
    if(sem_unlink(semaphore_name) == -1 ) {
        perror("nie udało się usunąć semafora\n");
    }
    return;
}
/*zamykanie semafora*/
void semaphore_close(sem_t* sem) {
    if (sem_close(sem) == -1) {
        perror("nie udało się zamknąć semafora\n");
        exit(1);
    }
    return;
}
/*opuszczanie semafora*/
void semaphore_wait(sem_t* sem) {
    if (sem_wait(sem)==-1) {
        perror("wait error");
        exit(1);
    }
    return;
}
/*podnoszenie semafora*/
void semaphore_post(sem_t* sem) {
    if (sem_post(sem) == -1) {
        perror("post error");
        exit(1);
    }
}
/*zwracanie aktualnej wartości semafora*/
int semaphore_get_value(sem_t* sem) {
    int val;
    if(sem_getvalue(sem, &val) == -1) {
        perror("sem getvalue error");
        exit(1);
    }
    return val;
}
