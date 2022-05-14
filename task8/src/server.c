#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "include/server.h"
#include "include/msg_handlers.h"

/*funkcja wyjścia*/
void exit_handler() {
    mq_unlink(MESSAGE_QUEUE_NAME);
}
/*funkcja obsługi SIGINT*/
void sig_handler() {
    printf("\n[SERVER] otrzymano sygnał SIGINT, usuwanie kolejki\n");
    exit_handler();
    _exit(1);
}
/*funkcja odpowiedzialna za interpretowanie otrzymanej od kilenta wiadomości*/
void input_parser(char *str,char* queue_name, int* num1, int* num2, char* operator) {
    strcpy(queue_name, strtok(str, " "));
    *num1 = atoi(strtok(NULL, " "));
    *operator = strtok(NULL, " ")[0];
    *num2 = atoi(strtok(NULL, " "));
}
/*funkcja zwracająca wynik zapytania klienta*/
int compute (int num1, char operator, int num2) {
    int answer;
    if (operator == '+') {
        answer = num1 + num2;
    } else if( operator == '-') {
        answer = num1 - num2;
    } else if (operator == '*') {
        answer = num1 * num2;
    } else {
        answer = num1 / num2;
    }
    return answer;
}
int main() {
    /*kolejka serwera*/
    mqd_t queue;

    char buffer[MSGSIZE];
    char client_queue_name[20];
    int num1;
    int num2;
    char operator;
    mqd_t client_queue;

    /*rejestrowanie funkcji wyjścia i obsługi sygnału*/
    if(atexit(exit_handler)!=0) {
        perror("atexit error");
        exit(1);
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        perror("signal error");
        exit(1);
    }

    /*tworzenie kolejki serwera*/
    queue = msg_create(MESSAGE_QUEUE_NAME);
    printf("[SERVER] >> utworzono kolejkę >> NAME: %s >> DES: %d >> MAXMSG: %d >> MSGSIZE: %d\n", MESSAGE_QUEUE_NAME, queue, MAXMSG, MSGSIZE);

    while (1) {
        /*odbieranie zapytania od klienta*/ 
        msg_receive(queue, buffer);
        /*przetwarzanie otrzymanych danych*/
        input_parser(buffer, client_queue_name, &num1, &num2, &operator);

        printf("[SERVER] >> otrzymano zapytanie od procesu: %s >> TREŚĆ: %d %c %d\n", client_queue_name, num1, operator, num2);
       
        /*otwarcie kolejki klienta*/
        client_queue = msg_open(client_queue_name, O_WRONLY);

        /*usunięcie znaku '/' z nazwy*/
        memmove(client_queue_name, client_queue_name + 1, strlen(client_queue_name));

        printf("[SERVER] >> otworzono kolejkę klienta o PID: %s\n", client_queue_name);

        sprintf(buffer, "%d", compute(num1, operator, num2));
        
        /*wysłanie odpowiedzie na zapytanie klienta*/
        msg_send(client_queue, buffer);

        printf("[SERVER] >> wysłano odpowiedź do klienta o PID: %s\n", client_queue_name);

        /*zamknięcie kolejki klienta*/ 
        msg_close(client_queue);
    }
    /*zamknięcie kolejki serwera*/
    msg_close(queue);
    return 0;
}
