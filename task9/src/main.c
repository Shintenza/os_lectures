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

unsigned random_gen(int down, int up) {
    return (rand() % (up - down + 1)) + down;
}

void* thread_callback(void* arg) {
    struct CallbackArgs *data = arg;
    int id = data->id;
    unsigned local_counter;
    sleep(data->number_of_threads);

    for (int i = 0; i < data->number_of_sections; i++) {

        gotoxy(0, id + data->number_of_threads + 1);
        printf("[PRZED]::[%d]::[ITER: %d]", id, i);

        pthread_mutex_lock(&data->mutex);

        gotoxy(50, id + data->number_of_threads + 1);

        printf("[W]::[%d]::[ITER: %d]\n", id, i);
        local_counter = *data->counter;
        local_counter++;

        sleep(2);

        gotoxy(50, id + data->number_of_threads + 1);
        printf("\033[2K]");

        *data->counter = local_counter;

        pthread_mutex_unlock(&data->mutex);

        gotoxy(0, id + data->number_of_threads + 1);
        printf("\033[K");
        printf("[PO]::[%d]::[ITER: %d]\n", id, i);
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Nieprawidłowa liczba argumentów. Składnia: [licza_wątków] [liczba sekcji krytycznych]\n");
        exit(1);
    }
    unsigned global_counter = 0;
    unsigned thread_n = atoi(argv[1]);
    unsigned section_n = atoi(argv[2]);

    pthread_t threads[atoi(argv[1])];

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    static struct CallbackArgs args;
    args.number_of_threads = thread_n;
    args.number_of_sections = section_n;
    args.mutex = mutex;
    args.counter = &global_counter;

    clear();
    gotoxy(0,0);
    for (int i = 0; i < atoi(argv[1]); i++) {
        args.id = i;
        pthread_create(&threads[i], NULL, thread_callback, &args);
        printf("[INFO] >> utworzono wątek nr. %d o adresie: %ld\n", i, threads[i]);
        sleep(1);
    }
    for (int i=0; i < atoi(argv[1]); i++) {
        pthread_join(threads[i], NULL);
    }

    printf("[INFO] >> wartość licznika: %d\n", global_counter);
    return 0;
}

