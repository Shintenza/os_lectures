#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <fcntl.h>

/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 17.04.2022*/
/*======================================================================================*/

/*generowanie liczb losowych*/
unsigned random_gen(int down, int up) {
    return (rand() % (up - down + 1)) + down;
}

int main (int argc, char** argv) {
    int filedes[2];
    int source; 
    int out;

    char buffer[PIPE_BUF] = {0};
    char out_msg[PIPE_BUF + 69];
    unsigned size;
    unsigned count;

    /*sprawdzenie czy zostały podane argumenty*/
    if ( argc< 2) {
        fprintf(stderr, "Niepoprawna składnia programu! Użyj ./task [input file] [output file]\n");
        exit(1);
    }

    source = open(argv[1], O_RDONLY);
    out = open("./output.txt", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);

    /*sprawdzenie czy pliki zostały poprawnie otwarte*/
    if (source == -1 || out == -1) {
        fprintf(stderr, "Podany plik wejściowy/wyjściowy nie istnieje lub nie jest do odczytu!\n");
        exit(1);
    }
    /*utworzenie potoku i sprawdzenie czy operacja się powiodła*/
    if (pipe(filedes) == -1) {
        perror("Pipe error");
        exit(1);
    }

    switch (fork()) {
        /*fork error*/
        case -1:
            perror("fork error");
            exit(1);
        /*proces potomny będący producentem*/
        case 0:
            /*zamknięcie deskryptora odczytu*/
            if (close(filedes[0]) == -1) {
                perror("close error");
                exit(1);
            }
            /*pętla odpowiedzialna za czytanie pliku i wstawianie losowo dużych fragmentów pliku tekstowego do potoku*/
            do {
                /*losowanie wielkości porcji danych która będzie umieszczona w potoku*/
                size = (rand() % (100 - 10 + 1)) + 10;
                /*czytanie size porcji danych z pliku źródłowego*/
                count = read(source, buffer, size);
                /*handlowanie ewentualnego błędu*/
                if (count == -1) {
                    perror("read error");
                    exit(1);
                }
                /*wstawienie znaku kończącego na koniec odczytanego tekstu i zdefiniowanie wyjścia*/
                buffer[count] ='\0';
                sprintf(out_msg, "[PRODUCER] - %s\n", buffer);

                /*losowy czas oczekiwania symulujący różne czasy przetwarzania danych*/
                sleep(random_gen(0, 3));
                
                /*wypisanie na ekran pobranej porcji danych, a także jej umieszczenie w potoku*/
                if (write(1, out_msg, strlen(out_msg)) == -1 || write(filedes[1], buffer, count) == -1 ) {
                    perror("write error");
                    exit(1);
                }
            } while (count > 0);

            /*zamknięcie potoku*/
            if (close(filedes[1]) == -1) {
                perror("close error");
                exit(1);
            }
            break;
        /*proces rodzic będący konsumentem*/
        default:
            /*zamknięcie nieużywanej części potoku*/
            if (close(filedes[1]) == -1) {
                perror("close error");
                exit(1);
            }
            /*czytanie z potoku do momentu kiedy jest pusty*/
            while ((count = read(filedes[0], buffer, PIPE_BUF) ) > 0) {
                /*wypisanie pobranych danych z potoku do pliku wyjściowego*/
                if (write(out, buffer, count) == -1) {
                    perror("parent write error");
                    exit(1);
                }
                /*tworzenie wiadomości zwrotnej i wypisanie jej na ekran*/
                buffer[count] = '\0';
                sprintf(out_msg, "[KONSUMENT] - %s\n", buffer);

                if (write(2, out_msg, strlen(out_msg)) == -1) {
                    perror("parent write error");
                    exit(1);
                }
            }
            /*handlowanie błędu funkcji read (pętla while)*/
            if (count == -1) {
                perror("read error");
                exit(1);
            }
            /*zamknięcie potku po fachowej robocie*/
            if (close(filedes[0]) == -1) {
                perror("close error");
                exit(1);
            }
            break;
    }
    return 0;
}
