#include "include/bakery.h"
#define OFFSET 4
#define SPACING 80

/*funkcja generująca losowe liczby z przedziału*/
unsigned random_gen(int down, int up) {
    return (rand() % (up - down + 1)) + down;
}

/*funkcja znajdująca największą wartość w tablicy*/
int get_max (int *nums, int size) {
    int max = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}

/*funkcja realizująca wzajemne wykluczanie wątków*/
void* bakery(void* data) {
    CallbackArgs *args = data;
    int id = args->id;
    unsigned local_counter;

    sleep(args->n_threads);

    for (int i = 0; i < args->n_sections; i++) {
        /* SEKCJA PRYWATNA*/
        printf("\033[%d;%dH[INFO]::[ID: %d]::[ITER: %d] >> sekcja prywatna\033[K", OFFSET +id, 0, id, i);
        fflush(stdout);

        args->choosing[id] = 1;
        args->number[id] = get_max(args->number, args->n_threads) + 1;
        args->choosing[id] = 0;

        /*zmiana kursora na linię przeznaczoną dla danego wątka*/
        for (int j = 0; j < args->n_sections; j++) {
            while(args->choosing[j]);
            while(args->number[j] != 0 && (args->number[j] < args->number[id] || (args->number[j] == args->number[id] && j < id)));
        }

        /*SEKCJA KRYTYCZNA*/
        gotoxy(SPACING, OFFSET + id);
        printf("\033[K");
        printf("[IN]::[ITER %d]", i);
        fflush(stdout);
        
        /*pobranie wartości globalnego licznika do zmiennej lokalnej oraz jej inkrementacja*/
        local_counter = *args->global_counter;
        local_counter++;

        /*losowy czas oczekiwania*/
        sleep(random_gen(1,3));
        gotoxy(SPACING, OFFSET + id);
        printf("\033[K");
        gotoxy(0, OFFSET + id);
        printf("\033[m");
        
        /*ustawienie globalnej watości licznika na powiększoną o 1*/
        *args->global_counter = local_counter;
        
        /*KONIEC SEKCJI PRYWATNEJ*/
        args->number[id] = 0;
    }
    return NULL;
}
