#include "include/mem_handlers.h"

/*tworzenie pamięci dzielonej*/
int mem_create(char* name, size_t size) {
    int fd;
    fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("shm create error");
        exit(1);
    }
    if (ftruncate(fd, size) == -1) {
        perror("ftruncate error");
        exit(1);
    }
    return fd;
}
/*otwieranie pamięci dzielonej*/
int mem_open(char* name) {
    int fd;
    fd = shm_open(name, O_RDWR, 0644);
    if (fd == -1) {
        perror("failed to open shared memory");
        exit(1);
    }
    return fd;
}
/*zamknięcie pamięci dzielonej*/
void mem_close(int fd) {
    if (close(fd) == -1 ){
        perror("close error");
        exit(1);
    }
}
/*usunięcie pamięci dzielonej*/
void mem_destroy(char* name) {
    if(shm_unlink(name) == -1 ) {
        perror("unlink error");
    }
}
/*mapowanie pamięci dzielonej w przestrzeń adresową procesu*/
void* mem_map(int fd, size_t size) {
    void *map = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    return map;
}
/*usunięcie odwzorowania pamięci dzielonej procesu*/
void mem_unlink(void* addr, size_t length) {
    if (munmap(addr, length) == -1 ) {
        perror("unmap error");
    }
}
