#ifndef MEM_HANDLERS_H
#define MEM_HANDLERS_H
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/types.h>

#define N_ELE 21
#define N_BUF 5

typedef struct {
    char buffer[N_BUF][N_ELE];
    unsigned in_index;
    unsigned out_index;
    int end_mark;
} SegWrapper;

int     mem_create (char* name, size_t size);
int     mem_open(char* name);
void    mem_close(int fd);
void    mem_destroy(char* name);
void*   mem_map(int fd, size_t size);
void    mem_unlink(void* addr, size_t length);
#endif
