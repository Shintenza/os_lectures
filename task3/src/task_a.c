#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE
#define _XOPEN_SOURCE 500

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistdio.h>
#include <unistd.h>
#include <signal.h>

#include "utils.h"
/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 27.03.2022*/
/*======================================================================================*/

/*Program służący do obsługi sygnałów*/


/*Wlasna funkcja obslugujaca zadany jej sygnal*/
void signal_handler (int signal) {
    /*o ile internet nie klamie dostep do sys_siglist jest zabroniony od wersji 2.32*/
    const char *str;
    if ((str = sigabbrev_np(signal)) == NULL) {
        fprintf(stderr, "Niepoprawny sygnał");
        exit(1);
    }
    printf("[INFO::A] >> PID: %d >> SIG%s\n", getpid(), str); }

int main (int argc, char **argv) {
    int given_mode;
    int given_signal;

    /*wczytywanie zmiennych*/
    given_mode = load_input(argc, argv, 1);
    given_signal = load_input(argc, argv, 2);

    /*przelacznie sposobu reakcji na zadany sygnal*/
    printf("[INFO::A] >> PID: %d >> PGID: %d >>GIVEN_MODE: %d >> GIVEN_SIGNAL: %d\n", getpid(), getpgid(0), given_mode, given_signal);

    switch (given_mode) {
        /*domyślne zachowanie w przypadku otrzymania sygnału*/
        case 0:
            if (signal(given_signal, SIG_DFL)==SIG_ERR) {
                perror("Funkcja signal poległa :(");
                exit(1);
            }
            pause();
            break;
        /*ignorowanie w przypadku otrzymania sygnału*/
        case 1:
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
