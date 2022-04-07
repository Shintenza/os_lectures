#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#include "utils.h"
/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 29.03.2022*/
/*======================================================================================*/
/*Program tworzący proces potomny, który staje się liderem swojej grupy i tworzy procesy potomne. Następnie program wysyła sygnały do całej grupy*/

/*Makra określające położenie i nazwę uruchomianego programu za pomocą execlp*/
#define PROGRAM_NAME "task_c2"
#define PROGRAM_PATH "./bin/"

int main (int argc, char **argv) {
    char given_mode[2];
    int given_signal;

    char path[30];
    pid_t children_pid;
  
    /*odczytywanie sygnału*/
    given_signal = load_input(argc, argv, 2);
    /*odczytywanie trybu odpowiedzi na dany proces*/
    sprintf(given_mode, "%d", load_input(argc, argv, 1));
    /*Tworzenie scieżki do pliku binarnego*/
    sprintf(path, "%s%s", PROGRAM_PATH, PROGRAM_NAME);
    

    /*proces potomny*/
    switch (children_pid = fork()) {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            /*ustanowienie procesu liderem grupy*/
            if (setpgid(0,0) == -1) {
                perror("setpgid error");
                exit(1);
            }
            // TODO error handling
            if (execlp(path, PROGRAM_NAME, given_mode, argv[2], NULL)==-1){
                perror("exec problem");
                exit(1);
            }
            break;
        default:
            /*proces macierzysty*/
            sleep(3);
            /*sprawdzenie czy utworzony proces istnieje*/
            if(kill(children_pid, 0)==-1){
                perror("Nie znaleziono procesu potomnego!");
                exit(1);
            }
            /*zdobycie PGID procesu potomnego*/
            if((children_pid = getpgid(children_pid))==-1) {
                perror("Nie udało się zdobyć PGID procesu");
                exit(1);
            }
            
            if(kill(-children_pid, 0)==-1) {
                perror("Nie udało się wysłać sygnału do grupy");
                exit(1);
            }
            printf("[INFO::C] >> wysłano sygnał\n");
            kill(-children_pid, given_signal);
            wait(NULL);
            break;
    }
    return 0;
}
