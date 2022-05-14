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
int str_to_num (char* str, int* num) {
    char* error = NULL;
    *num = strtod(str, &error);
    if (*error != '\0') {
        return -1;
    }
    return 0;
}
/*funkcja odpowiedzialna za interpretowanie otrzymanej od kilenta wiadomości*/
int input_parser(char *str,char* queue_name, int* num1, int* num2, char* operator) {
    char *tmp = strtok(str, " ");
    int converted_num;
    if (tmp == NULL) {
        return -1;
    }
    strcpy(queue_name, tmp);
    tmp = strtok(NULL, " ");
    if (tmp == NULL) {
        return -1;
    }
    if (str_to_num(tmp, &converted_num) == -1) {
        return -1;
    }
    *num1 = converted_num;
    tmp = strtok(NULL, " ");
    if (tmp == NULL) {
        return -1;
    }
    *operator = tmp[0];
    tmp = strtok(NULL, " ");
    if (tmp == NULL) {
        return -1;
    }
    tmp[strlen(tmp) - 1] = '\0';
    if (str_to_num(tmp, &converted_num) == -1) {
        return -1;
    }

    *num2 = converted_num;
    return 0;
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
    int parser_return_value;
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
        parser_return_value = input_parser(buffer, client_queue_name, &num1, &num2, &operator);
        printf("[SERVER] >> otrzymano zapytanie od procesu: %s >> TREŚĆ: %d %c %d\n", client_queue_name, num1, operator, num2);
           
        /*otwarcie kolejki klienta*/
        client_queue = msg_open(client_queue_name, O_WRONLY);
        printf("[SERVER] >> otworzono kolejkę klienta o PID: %s\n", client_queue_name);

        /*walidacja poprawności składni polecenia*/
        if (parser_return_value == 0) {
            /*usunięcie znaku '/' z nazwy*/
            memmove(client_queue_name, client_queue_name + 1, strlen(client_queue_name));
            
            /*wykonanie obliczenia i zapisanie do bufora*/
            sprintf(buffer, "%d", compute(num1, operator, num2));
        } else {
            sprintf(buffer, "[ERROR] >> niepoprawna składnia zapytania\n");
        }

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
