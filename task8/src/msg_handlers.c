#include "include/msg_handlers.h"

/*tworzenie kolejki komunikatów*/
mqd_t msg_create(const char* name) {
    struct mq_attr attr = { 0, MAXMSG, MSGSIZE, 0};
    mqd_t msg_queue = mq_open(name, O_RDONLY | O_CREAT | O_EXCL, 0644, &attr);
    if (msg_queue == -1) {
        perror("failed to create msg queue");
        exit(1);
    }
    return msg_queue;
}
/*otwieranie kolejki komunikatów w podanym przez użytkownika trybie*/
mqd_t msg_open(const char* name, int mode) {
    mqd_t msg_queue = mq_open(name, mode);
    if (msg_queue == -1) {
        perror("failed to open given queue");
        exit(1);
    }
    return msg_queue;
}
/*zamknięcie kolejki*/
void msg_close (mqd_t des) {
    if (mq_close(des) == -1) {
        perror("failed to close given queue");
        exit(1);
    }
}
/*usunięcie kolejki*/
void msg_delete (const char* name) {
    if (mq_unlink(name) == -1) {
        perror("failed to delete given queue");
        exit(1);
    }
}
/*nadanie komunikatu za pomocą kolejki*/
void msg_send (mqd_t des, char* buffer) {
    if (mq_send(des, buffer, MSGSIZE, 1) == -1 ) {
        perror("failed to send a payload");
        exit(1);
    }
}
/*odebranie komunikatu za pomocą kolejki*/
void msg_receive (mqd_t des, char* buffer) {
    if (mq_receive(des, buffer, MSGSIZE, 0) == -1) {
        perror("failed to receive payload");
        exit(1);
    }
}
