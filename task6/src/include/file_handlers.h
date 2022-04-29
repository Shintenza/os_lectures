#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int open_rd(const char* filename);
int open_rw(const char* filename);
void read_file(int fd, char* buffer);
void close_file(int fd);
void write_file(int fd, char* str);
