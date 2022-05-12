#include "include/file_handlers.h"
#include "include/sem_handlers.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define READ_BUF_SIZE 10

unsigned rand_time () {
    return rand() % 5;
}

int main (int argc, char** argv) {
    const char* sem_name = argv[1];
    const char* file_name = argv[3];
    const int number_of_sections = atoi(argv[2]);
    char read_buffer[READ_BUF_SIZE];
    int i;
    int num_file;
    int sem_value;
    int file_number;
    sem_t* sem;

    /*otwarcie wcześniej utworzonego semafora*/ 
    sem = semaphore_open(sem_name);

    /*pętla wykonujaca się number_of_sections razy*/
    for(i = 0; i < number_of_sections; i++) {
        /*wydobycie wartości semafora*/
        sem_value = semaphore_get_value(sem);

        printf("[INFO]::[PID: %d]::[SEM_V: %d] >> przed sekcją krytyczną\n", getpid(), sem_value);
        
        /*operacja opuszczania semafora*/
        semaphore_wait(sem);

        /*sekcja krytyczna*/

        sem_value = semaphore_get_value(sem);
        sleep(rand_time());
        printf(">>>>[INFO]::[PID: %d]::[SEM_V: %d]::[ITER: %d] >> sekcja krytyczna\n", getpid(), sem_value, i);
        
        /*otwarcie pliku tekstowego, wczytanie jego zawartości i jej inkrementacja*/
        num_file = open_rd(file_name);
        read_file(num_file, read_buffer);
        close_file(num_file);

        file_number = atoi(read_buffer);
        file_number++;
        sprintf(read_buffer, "%d", file_number);

        num_file = open_rw(file_name);
        write_file(num_file, read_buffer);
        close_file(num_file);

        /*koniec sekcji krytycznej*/
        
        /*podnoszenie semafora po sekcji krytycznej*/
        semaphore_post(sem);
         
        sem_value = semaphore_get_value(sem);
        printf("[INFO]::[PID: %d]::[SEM_V: %d] >> po sekcji krytycznej\n", getpid(), sem_value);
    }
    semaphore_close(sem);
}
