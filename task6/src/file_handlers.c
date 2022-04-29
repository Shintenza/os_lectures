#include "include/file_handlers.h"

int open_rd(const char* file_name) {
    int fd;
    fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    return fd;
}
int open_rw(const char* file_name) {
    int fd;
    fd = open(file_name, O_WRONLY | O_TRUNC | O_APPEND, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }
    return fd;
}
void read_file(int fd, char* buffer) {
    if (read(fd, buffer, sizeof(buffer)) == -1) {
        perror("read error");
        exit(1);
    }
}
void close_file(int fd) {
    if (close(fd) == -1) {
        perror("close error");
        exit(1);
    }
}
void write_file(int fd, char* str) {
    if (write(fd, str, sizeof(str)) == -1)  {
        perror("write error");
        exit(1);
    }
}
