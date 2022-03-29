#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE
#define _XOPEN_SOURCE 500

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
    int given_mode;
    int given_signal;

    /*sprawdzenie czy uzytkownik podal odpowiednia liczbe argumentow*/
    if (argc < 3) {
        fprintf(stderr, "Nie podano sposobu reakcji na sygnał i sygnału\n");
        exit(1);
    }

    given_mode = load_input(argc, argv, 1);
    given_signal = load_input(argc, argv, 2);

    /*sprawdzenie czy podany tryb działania mieści się w przedziale*/
    if (!(given_mode>=0 && given_mode <3)) {
        fprintf(stderr, "Podana wartość musi być liczbą z zakresu [0,2]\n");
        exit(1);
    }
    /*przelacznie sposobu reakcji na zadany sygnal*/
    printf("[INFO] >> PID: %d >> PGID: %d >>GIVEN_MODE: %d >> GIVEN_SIGNAL: %d\n", getpid(), getpgid(0), given_mode, given_signal);

    switch (given_mode) {
        case 0:
            signal(given_signal, SIG_DFL);
            pause();
            break;
        case 1:
            /*ignorowanie sygnału SIGQUIT*/
            if (signal(given_signal, SIG_IGN)==SIG_ERR) {
                perror("Funkcja signal poległa :(");
                exit(1);
            }
            break;
        case 2:
            /*własna obsługa sygnału SIGQUIT*/
            if (signal(given_signal, signal_handler)==SIG_ERR) {
                perror("Funkcja signal poległa :(");
                exit(1);
            }
            pause();
            break;
    }
    return 0;
}
