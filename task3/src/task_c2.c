#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#include "utils.h"

/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 27.03.2022*/
/*======================================================================================*/
/*Program ustanawia się liderem grupy, tworzy procesy potomne, ignoruje przychodzący sygnał, zarządza dziećmi i wypisuje ich status*/

#define PROGRAM_NAME "task_a"
#define PROGRAM_PATH "bin/"

/*liczba wywołań komendy fork*/
#define FORK_NUMBER 3

int main (int argc, char **argv) {
    int status;
    int i;
    int given_signal = load_input(argc, argv, 2);
    pid_t waited_for;
    char path[30];

    sprintf(path, "%s%s", PROGRAM_PATH, PROGRAM_NAME);
    /*ustawienie ignorowania sygnału*/
    if (signal(given_signal, SIG_IGN)==SIG_ERR) {
        perror("Funkcja signal poległa :(\n");
        exit(1);
    }
    /*tworzenie procesów potomnych*/
    for (i=0; i < FORK_NUMBER; i++) {
        switch (fork()) {
            case -1:
                perror("fork error");
                exit(1);
                break;
            case 0:
                if(execlp(path, PROGRAM_NAME, argv[1], argv[2], NULL) ==-1) {
                    perror("błąd w uruchomianiu programu");
                    exit(1);
                }
                break;
            default:
                break;
        }
    }
    
    /*czekanie na procesy potomne, a także zbieranie i wyświetlanie ich statusów*/
    for (i=0; i< FORK_NUMBER; i++) {
        if((waited_for = wait(&status)==-1)) {
            perror("Wait error");
            exit(1);
        }
        printf("[INFO::C2] >> kod powrotu: >> %d\n", status);
    }
    printf("[INFO::C2] >> procesy potomne zakończone!\n");
    return 0;
}
