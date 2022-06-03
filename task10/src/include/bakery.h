#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

typedef struct CallbackArgs {
    unsigned* global_counter;
    int *choosing;
    int *number;
    int n_threads;
    int n_sections;
    int id;
} CallbackArgs;
void* bakery(void* arg);
