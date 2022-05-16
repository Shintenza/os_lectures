#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

struct CallbackArgs {
    unsigned number_of_threads;
    unsigned number_of_sections;
    unsigned *counter;
    int id;
    pthread_mutex_t mutex;
};

void* exclusion(void* arg);
