#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

#define MAXMSG 5
#define MSGSIZE 50

mqd_t msg_create(const char* name);
mqd_t msg_open(const char* name, int mode);

void msg_close(mqd_t des);
void msg_delete (const char* name);
void msg_send (mqd_t des, char* buffer);
void msg_receive (mqd_t des, char* buffer);
