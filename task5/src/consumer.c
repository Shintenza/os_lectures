#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 300

int main (int argc, char** argv) {
    int count;
    int fifo;
    int out;
    char buffer[BUF_SIZE];
    char out_msg[BUF_SIZE+50];

    /*sprawdzenie poprawności argumentów*/
    if (argc < 2) {
        fprintf(stderr, "Niewystarczająca liczba argumentów!. Składnia: ./consumer [nazwa potoku] [nazwa_pliku]\n");
        exit(1);
    }
    printf("[INFO] >> consumer started\n");

    fifo = open(argv[1], O_RDONLY);
    out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fifo == -1 || out == -1) {
        fprintf(stderr, "Problem z otwarciem plików fifo/out\n");
    }

    /*czytanie z potoku nazwanego*/
    while ((count = read(fifo, buffer, BUF_SIZE) ) > 0) {
        
        if (write(out, buffer, count) == -1) {
            perror("consumer write error");
            exit(1);
        }
        buffer[count] = '\0';
        sprintf(out_msg, "[CONSUMER] - %s\n", buffer);

        if (write(1, out_msg, strlen(out_msg)) == -1) {
            perror("consumer write error");
            exit(1);
        }
    }

    /*zwolnienie deskryptorów*/
    if (close(fifo) == -1 || close(out) ==-1 ) {
        perror("consumer close error");
        exit(1);
    }
    return 0;
}
