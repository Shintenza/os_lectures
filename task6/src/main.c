#include "include/file_handlers.h"
#include "include/sem_handlers.h"
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

#define SEM_NAME "/t_sem"
#define NUM_FILE "number.txt"
#define READ_BUF_SIZE 10

void exit_handler () {
    if(sem_unlink(SEM_NAME) == -1) {
        perror("sem unlink error");
    } else {
        printf("[INFO] >> usunięto semafor\n");
    }
}

void sig_handler () {
    semaphore_delete(SEM_NAME);
    printf("[INFO] >> otrzymano sygnał SIGINT, usunięto semafor\n");
    _exit(1);
}

int str_to_num (char *str) {
    char *end;
    int converted_num = strtod(str, &end);
    if (*end != '\0') {
        converted_num = -1;
    }
    return converted_num;
}

int main (int argc, char** argv) {
    sem_t *sem;
    char program_path[69];
    int process_number;
    int section_number;
    int i;
    int num_file;
    char read_buffer[READ_BUF_SIZE];
    
    if (argc < 4) {
        fprintf(stderr, "Niepoprawna składnia polecenia, poprawne użycie [nazwa_programu] [liczba_procesów] [liczba_sekcji]");
        exit(1);
    }
    if (atexit(exit_handler) != 0) {
        perror("atexit error");
        exit(1);
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("singal error");
        exit(1);
    }

    sem = semaphore_create(SEM_NAME);
    sprintf(program_path, "./bin/%s", argv[1]);
    process_number = str_to_num(argv[2]);
    section_number = str_to_num(argv[3]);

    if (process_number < 0 || section_number < 0) {
        fprintf(stderr, "Niepoprawna wartość liczby procesów/sekcji\n");
        exit(1);
    }
    
    num_file = open_rw(NUM_FILE);
    write_file(num_file, "0");
    close_file(num_file);

    for (i = 0; i<process_number; i++) {
        switch(fork()) {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                if (execlp(program_path, argv[1], SEM_NAME, argv[3], NUM_FILE, NULL) == -1) {
                    perror("execlp error");
                    _exit(1);
                }
        }
    }

    for (i = 0; i< process_number; i++) {
        if(wait(NULL) == -1) {
            perror("wait error");
            exit(1);
        }
    }

    num_file = open_rd(NUM_FILE);
    read_file(num_file, read_buffer);

    printf("[INFO] >> końcowa wartość pliku: %s\n", read_buffer);

    semaphore_close(sem);
    close_file(num_file);
}
