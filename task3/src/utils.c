#include <stdlib.h>
#include <stdio.h>

int load_input(int argc, char **argv, int element) {
    char *error;
    int converted_num;
    /*sprawdzenie czy użytkownik podał odpowiednią liczbę argumentów*/
    if (argc < 3) {
        fprintf(stderr, "Zła liczba argumentów! Musisz podać sposób obsługi sygnału, a także sygnał\n");
        exit(1);
    }
    converted_num = strtol(argv[element], &error, 10);

    /*sprawdzenie czy podana wartość była liczbą*/
    if (*error!='\0') {
        fprintf(stderr, "Podana wartość musi być liczbą\n");
    }

    /*sprawdzenie czy podany sposób obsługi sygnałów jest poprwany*/
    if (element == 1 && (!(converted_num>=0 && converted_num <3))) {
        fprintf(stderr, "Podana wartość musi być liczbą z zakresu [0,2]\n");
        exit(1);
    }

    return converted_num;
}
