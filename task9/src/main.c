#define _REENTRANT

#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "include/exclusion.h"

int main(int argc, char** argv) {
    /*sprawdzenie poprawnej liczby argumentów*/
    if (argc < 3) {
        fprintf(stderr, "[ERROR] >> nieprawidłowa liczba argumentów. Składnia: [licza_wątków] [liczba_sekcji_krytycznych]\n");
        exit(1);
    }
    /*zmienna zawierająca licznik inkrementowany przez wątki*/
    unsigned global_counter = 0;

    /*liczba tworzonych wątków, a także sekcji krytycznych*/
    unsigned thread_n = atoi(argv[1]);
    unsigned section_n = atoi(argv[2]);
    
    /*zmienna przechowująca muteks*/
    pthread_mutex_t mutex;
    /*tablica identyfikatorów utworzonych wątków*/
    pthread_t threads[atoi(argv[1])];
    /*struktura zawierająca argumenty przekazywane funkcji realizującej wzajemne wykluczanie wątków*/
    static struct CallbackArgs args;
    int return_value;

    /*inicjowanie muteksu*/
    if ((return_value = pthread_mutex_init(&mutex, NULL)) != 0 ) {
        fprintf(stderr, "Nie udało się utworzyć muteksu: %s\n", strerror(return_value));
        exit(1);
    }
    /*wyczyszczenie ekranu i umieszczenie kursora w lewym górnym rogu*/
    clear();
    gotoxy(0,0);

    printf("[INFO] >> zainicjowano muteks o adresie %p\n", (void *)&mutex);

    /*ustawianie odpowiednich wartości dla struktury argumentów*/ 
    args.number_of_threads = thread_n;
    args.number_of_sections = section_n;
    args.mutex = mutex;
    args.counter = &global_counter;

    for (int i = 0; i < atoi(argv[1]); i++) {
        args.id = i;
        /*tworzenie wątków i umieszczanie ich identyfikatorów w tablicy*/
        if ((return_value = pthread_create(&threads[i], NULL, exclusion, &args)) != 0){
            fprintf(stderr, "nie udało się utworzyć wątku: %s\n", strerror(return_value));
        }
        printf("[INFO] >> utworzono wątek nr. %d o adresie: %ld\n", i, threads[i]);
        sleep(1);
    }
    
    /*oczekiwanie na zakończenie pracy wątków*/
    for (int i=0; i < thread_n; i++) {
        if ((return_value = pthread_join(threads[i], NULL)) != 0) {
            fprintf(stderr, "błąd w wykonaniu funkcji pthread_join: %s\n", strerror(return_value));
            exit(1);
        }
    }

    if ((return_value = pthread_mutex_destroy(&mutex)) != 0) {
        fprintf(stderr, "błąd usuwania muteksu %s\n", strerror(return_value));
        exit(1);
    }
    if (global_counter == thread_n * section_n) {
        printf("\n[INFO] otrzymano oczekiwaną wartość wynoszącą: %d\n", global_counter);
    } else {
        printf("\n[INFO] otrzymano niepoprawną wartość (%d)\n", global_counter);
    }
    return 0;
}

