#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include "utils.h"
/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 27.03.2022*/
/*======================================================================================*/

/*Makra określające położenie i nazwę uruchomianego programu za pomocą execlp*/
#define PROGRAM_NAME "task_a"
#define PROGRAM_PATH "./bin/"

/*Funkcja do wczytywania od użytkownika trybu działania z obsługą błędów*/
int main(int argc, char **argv) {
    pid_t child_pid;
    char given_mode[2];
    int given_signal;
    char path[30];
    
    given_signal = load_input(argc, argv, 2);
    sprintf(given_mode, "%d", load_input(argc, argv, 1));

    /*Tworzenie scieżki do pliku binarnego*/
    sprintf(path, "%s%s", PROGRAM_PATH, PROGRAM_NAME);

    switch(child_pid = fork()){
        case -1:
            perror("Fork problem");
            exit(1);
        case 0:
            if (execlp(path, PROGRAM_NAME, given_mode, argv[2], NULL)==-1) {
                perror("exec error; check the given program name");
                exit(1);
            }
            break;
        default:
            /*Wysłanie sygnału 0 aby sprawdzić czy dany proces istnieje*/
            if (kill(child_pid, 0)==-1) {
                perror("Nie znaleziono procesu potomnego!\n");
                exit(1);
            }
            sleep(2);
            /*sprawdzenie czy sygnał został poprawnie wysłany*/
            printf("[INFO::B] >> wysłano sygnał\n");
            if(kill(child_pid, given_signal)==-1) {
                perror("Problem z wysłaniem sygnału :(\n");
                exit(1);
            }
            if(wait(NULL) == -1) {
                perror("wait error");
                exit(1);
            }
            break;
    }
}
chuj;
