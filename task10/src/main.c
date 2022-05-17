#include <stdio.h>
#include <unistdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "include/bakery.h"



int main (int argc, char** argv) {
    /*sprawdzenie czy podana liczba argumentów jest poprawna*/
    if (argc < 3) {
        fprintf(stderr, "[ERROR] >> zła liczba argumentów. Składnia: [liczba_wątków] [liczba_sekcji_krytycznych]\n");
        exit(1);
    }

    /*liczba wątków odczytana od użytkownika*/
    int n_threads = atoi(argv[1]);
    /*liczba sekcji krytycznych odczytana od użytkownika*/
    int n_sections = atoi(argv[2]);
    /*globalny licznik inkrementowany przez wątki*/
    unsigned counter = 0;
    /*tablica zawierająca identyfikatory wątków*/
    pthread_t threads[n_threads];

    /*struktura zawierająca potrzebne dla funkcji realizującej algorytm piekarni*/
    CallbackArgs args; 

    args.choosing = calloc(n_threads, sizeof(int));
    args.number = calloc(n_threads, sizeof(int));
    args.n_sections = n_sections;
    args.n_threads = n_threads;
    args.global_counter = &counter;

    /*czyszczenie ekranu i ustawienie początkowe kursora*/
    clear();
    gotoxy(0,0);

    for (int i = 0; i < n_threads; i++){
        args.id = i;
        /*tworzenie wątków i umieszczanie ich identyfikatorów w tablicy*/
        if (pthread_create(&threads[i], NULL, bakery, &args) != 0){
            fprintf(stderr, "nie udało się utworzyć wątka\n");
        }
        printf("[INFO] >> utworzono wątek nr. %d o adresie: %ld\n", i, threads[i]);
        sleep(1);
    }

    /*oczekiwanie na zakończenie pracy wątków*/
    for (int i=0; i < n_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "błąd w wykonaniu funkcji pthread_join\n");
            exit(1);
        }
    }
    
    /*sprawdzenie i wypisanie końcowych wyników*/
    if (n_threads * n_sections == counter ) {
        printf("\n[INFO] >> otrzymano poprawną wartość licznika: %d\n", counter);
    } else {
        printf("\n[INFO] >> otrzymano niepoprawną wartość licznika: %d\n", counter);
    }
    
    /*zwolnienie pamięci*/
    free(args.choosing);
    free(args.number);
    return 0;          
}                     
 
