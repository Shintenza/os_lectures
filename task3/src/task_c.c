#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 29.03.2022*/
/*======================================================================================*/

/*Makra określające położenie i nazwę uruchomianego programu za pomocą execlp*/
#define PROGRAM_NAME "task_c2"
#define PROGRAM_PATH "./"

int load_input(int argc, char **argv, int element) {
    char *error;
    int converted_num;
    /*sprawdzenie czy użytkownik podał odpowiednią liczbę argumentów*/
    if (argc < 3) {
        fprintf(stderr, "Nie podano sposobu obsługi sygnału\n");
        exit(1);
    }
    converted_num = strtol(argv[element], &error, 10);

    /*sprawdzenie czy podana wartość była liczbą*/
    if (*error!='\0') {
        fprintf(stderr, "Podana wartość musi być liczbą\n");
    }
    return converted_num;
}

int main (int argc, char **argv) {
    char given_mode[2];
    int given_signal;

    char path[30];
    pid_t children_pid;
   
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
            sleep(5);
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
            printf("[INFO] >> wysłano sygnał\n");
            kill(-children_pid, given_signal);
            wait(NULL);
            break;
    }
    return 0;
}
