#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 300

/*generowanie liczb losowych*/
unsigned random_gen(int down, int up) {
    return (rand() % (up - down + 1)) + down;
}

int main (int argc, char** argv) {
    int fifo;
    int source;
    int piece_size;
    char buffer[BUF_SIZE];
    char out_msg[BUF_SIZE + 50];
    int count;

    printf("[INFO] >> producer started!\n");

    /*sprawdzenie podanych argumentów*/
    if (argc < 2)  {
        fprintf(stderr, "Niewystarczająca liczba argumentów. Składnia ./producer [nazwa potoku] [nazwa pliku]\n");
        exit(1);
    }

    fifo = open(argv[1], O_RDWR);
    source = open(argv[2], O_RDONLY);

    /*sprawdzenie czy pliki zostały poprawnie otwarte*/
    if (fifo == -1 || source == -1) {
        fprintf(stderr, "Problem z otwarciem potoku/pliku źródłowego\n");
    }

    /*pętla odpowiedzialna za czytanie pliku i wstawianie losowo dużych fragmentów pliku tekstowego do potoku*/
    do {
        piece_size = (rand() % (100 - 10 + 1)) + 10;
        /*czytanie z pliku źródłowego losowej porcji danych*/
        count = read(source, buffer, piece_size);
        if (count == -1) {
            perror("producer read error");
            exit(1);
        }

        /*wstawienie znaku kończącego na koniec odczytanego tekstu i zdefiniowanie wyjścia*/
        buffer[count] ='\0';
        sprintf(out_msg, "[PRODUCER] - %s\n", buffer);
        /*symolowanie różnego czasu przetwarzania informacji*/
        sleep(random_gen(0, 3));

        /*zapisanie danych do potoku, a także wypisanie informacji na ekran*/
        if (write(1, out_msg, strlen(out_msg)) == -1 || write(fifo, buffer, count) == -1 ) {
            perror("producer write error");
            exit(1);
        }
    } while (count > 0);

    if (close(fifo) == -1 ) {
        perror("producer close error");
        exit(1);
    }
}
