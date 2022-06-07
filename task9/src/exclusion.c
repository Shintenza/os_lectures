#include "include/exclusion.h"
#include <string.h>

#define OFFSET 4
#define SPACING 70

/*funkcja generująca losowe liczby z przedziału*/
unsigned random_gen(int down, int up) {
    return (rand() % (up - down + 1)) + down;
}

/*funkcja realizująca wzajemne wykluczanie wątków*/
void* exclusion(void* arg) {
    struct CallbackArgs *data = arg;
    int id = data->id;
    unsigned local_counter;
    int return_value;
    sleep(data->number_of_threads);

    for (int i = 0; i < data->number_of_sections; i++) {
        /*przed sekcją krytyczną*/

        /*zmiana kursora na linię przeznaczoną dla danego wątka*/
        printf("\033[%d;%dH[INFO]::[ID: %d]::[ITER: %d] >> sekcja prywatna\033[K", OFFSET + data->number_of_threads + id, 0, id, i);
        fflush(stdout);

        /*sekcja krytyczna*/
        if ((return_value = pthread_mutex_lock(&data->mutex)) != 0) {
            fprintf(stderr, "mutex_lock error: %s\n", strerror(return_value));
            exit(1);
        }
        
        gotoxy(SPACING, OFFSET + id + data->number_of_threads);
        printf("\033[K");
        printf("[IN]::[ITER %d]", i);
        fflush(stdout);

        /*pobranie wartości globalnego licznika i zapisanie go w zmiennej lokalnej*/
        local_counter = *data->counter;
        /*inkrementacja licznika*/
        local_counter++;

        sleep(random_gen(1,3));

        /*aktualizacja globalnego licznika*/
        *data->counter = local_counter;

        gotoxy(SPACING, OFFSET + data->number_of_threads + id);
        printf("\033[K");
        gotoxy(0, OFFSET + data->number_of_threads + id);
        printf("\033[m");

        /*zwolnienie muteksu*/
        if ((return_value = pthread_mutex_unlock(&data->mutex)) != 0) {
            fprintf(stderr, "mutex_unlock error: %s\n", strerror(return_value));
            exit(1);
        }

        /*po sekcji krytycznej*/
    }
    return NULL;
}
