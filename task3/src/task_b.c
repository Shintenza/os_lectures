#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 27.03.2022*/
/*======================================================================================*/

/*Makra określające położenie i nazwę uruchomianego programu za pomocą execlp*/
#define PROGRAM_NAME "task_a"
#define PROGRAM_PATH "./"

/*Funkcja do wczytywania od użytkownika trybu działania z obsługą błędów*/
int load_input(int argc, char **argv, int element) {
    char *error;
    int converted_num;
    /*sprawdzenie czy użytkownik podał odpowiednią liczbę argumentów*/
    if (argc < 2) {
        fprintf(stderr, "Nie podano sposobu obsługi sygnału\n");
        exit(1);
    }
    converted_num = strtol(argv[element], &error, 10);

    /*sprawdzenie czy podana wartość była liczbą*/
    if (*error!='\0') {
        fprintf(stderr, "Podana wartość musi być liczbą\n");
    }

    /*sprawdzenie czy podana wartość była z odpowiedniego przedziału*/ 
    if (!(converted_num>=0 && converted_num <3)) {
        fprintf(stderr, "Podana wartość musi być liczbą z zakresu [0,2]\n");
        exit(1);
    }
    return converted_num;
}
int main(int argc, char **argv) {
    pid_t child_pid;
    char given_mode[2];
    char path[30];
    
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
            /* printf("PID rodzica: %d; PID potomka: %d\n", getpid(), child_pid); */
            /*Wysłanie sygnału 0 aby sprawdzić czy dany sygnał istnieje*/
            if (kill(child_pid, 0)==-1) {
                perror("Nie znaleziono procesu potomnego!\n");
                exit(1);
            }

            sleep(1);
            /*sprawdzenie czy sygnał został poprawnie wysłany*/
            if(kill(child_pid, 3)==-1) {
                perror("Problem z wysłaniem sygnału :(\n");
                exit(1);
            }
            break;
    }
}
