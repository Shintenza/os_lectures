#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

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

#define FORK_NUMBER 3
int main (int argc, char **argv) {
    int status;
    int i;
    int given_signal = load_input(argc, argv, 2);
    pid_t waited_for;

    if (signal(given_signal, SIG_IGN)==SIG_ERR) {
        perror("Funkcja signal poległa :(\n");
        exit(1);
    }
    for (i=0; i < FORK_NUMBER; i++) {
        switch (fork()) {
            case -1:
                perror("fork error");
                exit(1);
                break;
            case 0:
                if(execlp("./task_a", "task_a", argv[1], argv[2], NULL) ==-1) {
                    perror("błąd w uruchomianiu programu");
                    exit(1);
                }
                break;
            default:
                break;
        }
    }

    for (i=0; i< FORK_NUMBER; i++) {
        if((waited_for = wait(&status)==-1)) {
            perror("Wait error");
            exit(1);
        }
        printf("[INFO] >> kod powrotu: >> %d\n", status);
    }
    printf("[INFO] >> procesy potomne zakończone!\n");
    return 0;
}
