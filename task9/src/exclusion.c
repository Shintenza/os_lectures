#include "include/exclusion.h"

#define OFFSET 4

/*funkcja generująca losowe liczby z przedziału*/
unsigned random_gen(int down, int up) {
    return (rand() % (up - down + 1)) + down;
}

/*funkcja realizująca wzajemne wykluczanie wątków*/
void* exclusion(void* arg) {
    struct CallbackArgs *data = arg;
    int id = data->id;
    unsigned local_counter;
    sleep(data->number_of_threads);

    for (int i = 0; i < data->number_of_sections; i++) {
        /*przed sekcją krytyczną*/

        /*zmiana kursora na linię przeznaczoną dla danego wątka*/
        gotoxy(0, id + data->number_of_threads + OFFSET);
        printf("[PRZED]::[%d]::[ITER: %d]", id, i);

        /*sekcja krytyczna*/
        pthread_mutex_lock(&data->mutex);
        
        /*przesunięcie kursora w prawo i wypisanie informacji o wejściu do sekcji krytycznej*/
        gotoxy(50, id + data->number_of_threads + OFFSET);

        printf("[W]::[%d]::[ITER: %d]\n", id, i);

        /*pobranie wartości globalnego licznika i zapisanie go w zmiennej lokalnej*/
        local_counter = *data->counter;
        /*inkrementacja licznika*/
        local_counter++;

        sleep(random_gen(1,3));

        /*aktualizacja globalnego licznika*/
        *data->counter = local_counter;

        /*usunięcie informacji o byciu w sekcji krytycznej*/
        gotoxy(50, id + data->number_of_threads + OFFSET);
        printf("\033[2K]");

        /*zwolnienie muteksu*/
        pthread_mutex_unlock(&data->mutex);

        /*po sekcji krytycznej*/
        gotoxy(0, id + data->number_of_threads + OFFSET);
        printf("\033[K");
        printf("[PO]::[%d]::[ITER: %d]\n", id, i);
        fflush(stdout);

        sleep(1);
    }
    return NULL;
}
