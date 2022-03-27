#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistdio.h>
#include <unistd.h>
#include <signal.h>

/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 27.03.2022*/
/*======================================================================================*/

/*Wlasna funkcja obslugujaca zadany jej sygnal*/
void signal_handler (int signal) {
    /*o ile internet nie klamie dostep do sys_siglist jest zabroniony od wersji 2.32*/
    const char *str = sigabbrev_np(signal);
    printf("Siema, jestem procesem o PID: %d, a tu jest nazwa sygnału: SIG%s\n", getpid(), str);
}


int main (int argc, char **argv) {
    char *error; 
    int given_mode;

    /*sprawdzenie czy uzytkownik podal odpowiednia liczbe argumentow*/
    if (argc < 2) {
        fprintf(stderr, "Nie podano sposobu reakcji na sygnał!\n");
        exit(1);
    }

    given_mode = strtol(argv[1], &error, 10);

    /*sprawdzenie czy podany argument jest liczba i czy miesci sie w zakresie*/
    if (*error!='\0'){
        fprintf(stderr, "Podana wartość musi być liczbą\n");
        exit(1);
    }

    if (!(given_mode>=0 && given_mode <3)) {
        fprintf(stderr, "Podana wartość musi być liczbą z zakresu [0,2]\n");
        exit(1);
    }
    /*przelacznie sposobu reakcji na zadany sygnal*/
    switch (given_mode) {
        case 0:
            break;
        case 1:
            /*ignorowanie sygnału SIGQUIT*/
            if (signal(SIGQUIT, SIG_IGN)==SIG_ERR) {
                perror("Funkcja signal poległa :(\n");
                exit(1);
            }
            break;
        case 2:
            /*własna obsługa sygnału SIGQUIT*/
            if (signal(SIGQUIT, signal_handler)==SIG_ERR) {
                perror("Funkcja signal poległa :(\n");
                exit(1);
            }
            break;
    }
    /*przydatne w kopiowaniu do wywołania funkcji kill z poziomu powłoki*/    
    printf("[INFO] %d\n", getpid());
    pause();
    return 0;
}
