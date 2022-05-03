#ifndef SEM_HANDLERS_H
#define SEM_HANDLERS_H

#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

sem_t* semaphore_create(const char* semaphore_name);
sem_t* semaphore_open(const char* semaphore_name);
void semaphore_delete(const char* semaphore_name);
void semaphore_close(sem_t* sem);
void semaphore_wait(sem_t* sem);
void semaphore_post(sem_t* sem);
int semaphore_get_value(sem_t* sem);
#endif

