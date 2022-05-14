#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <signal.h>

#include "include/server.h"
#include "include/msg_handlers.h"

char queue_name[15];

void exit_handler() {
    mq_unlink(queue_name);
}
void sig_handler() {
    printf("\n[CLIENT] otrzymano sygnał SIGINT, usuwanie kolejki\n");
    exit_handler();
    _exit(1);
}

int main() {
    /*zmienna do przechowywania wejścia użytkownika*/
    char read_buffer[25];

    char buffer[MSGSIZE];

    /*kolejka odbierająca informacje od serwera*/
    mqd_t receive_queue;
    /*kolejka serwera*/
    mqd_t server_queue;

    sprintf(queue_name, "/%d", getpid());

    /*rejestrowanie funkcji wyjścia i obsługi sygnału SIGINT*/
    if(atexit(exit_handler)!=0) {
        perror("atexit error");
        exit(1);
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("signal error");
        exit(1);
    }
    
    /*utworzenie kolejki odbierającej informacje od serwera*/
    receive_queue = msg_create(queue_name);
    printf("[CLIENT] >> utworzono kolejkę >> NAME: %s >> DES: %d >> MAXMSG: %d >> MSGSIZE: %d\n", MESSAGE_QUEUE_NAME, receive_queue, MAXMSG, MSGSIZE);
    printf("[CLIENT::INFO] >> wpisz działanie matematyczne, pamiętaj aby użyć spacji między liczbą, a operatorem\n");

    /*otwarcie kolejki serwera w trybie do zapisu*/
    server_queue = msg_open(MESSAGE_QUEUE_NAME, O_WRONLY);

    while (1) {
        /*odczytanie wejścia od użytkownika*/
        if (fgets(read_buffer, sizeof(read_buffer), stdin) == NULL) {
            break;
        }
        /*zapisanie polecenia do tablicy znakowej*/
        sprintf(buffer, "%s %s", queue_name, read_buffer);
    
        /*wysłanie zapytania do serwera*/
        msg_send(server_queue, buffer);
        printf("[CLIENT] >> wysłano zapytanie: %s", buffer);

        /*oebranie odpowiedzi od serwera*/
        msg_receive(receive_queue, buffer);

        printf("[CLIENT] >> otrzymano odpowiedź od serwera: %s\n", buffer);
    }

    printf("[CLIENT] >> zakończono pracę klienta\n");

    /*zamknięcie nieużywanych kolejek*/
    msg_close(receive_queue);
    msg_close(server_queue);

    return 0;
}
