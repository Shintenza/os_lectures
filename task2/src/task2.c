#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/*======================================================================================*/
/* Kamil Kuziora                                                       Krakow 20.03.2022*/
/*======================================================================================*/

/* Opis programu */
/* Zadaniem programu jest wywolanie funkcji fork n-krotnie i uzycie funkcji exec do wywolania innego programu, ktory wypisze informace o potomnym procesie*/

/*liczba wykonan funkcji fork*/
#define FORK_LOOPS 3
/*pomocnicze macro do tworzenia sciezek do programu*/
#define PATH "./"

/*funkcja do zwracania sformatowanego tekstu zawierajacego poszegolne id*/
const char* get_pids () {
    static char output_msg[50];
    pid_t pgid = getpgid(0);
    if (pgid == -1) {
        perror("could't get pgid!\n");
    }
    sprintf(output_msg, "UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d", getuid(), getgid(), getpid(), getppid(), pgid);
    return output_msg;
}
/*Funkcja do uruchomiana zewnetrznego programu*/
void exec_program (char *program_path, char *first_arg, char *msg) {
    if (execlp(program_path, first_arg, msg, NULL)==-1) {
        perror("exec error; check the given program name");
        exit(1);
    }
}
int main(int argc, char** argv) {
    int i;
    char output_msg[100];
    char program_path[100];

    sprintf(output_msg, "%s", get_pids());
    sprintf(program_path, "%s%s", PATH, argv[1]);

    printf("%s\n", output_msg);

    for (i = 0; i < FORK_LOOPS; i++) {
        switch (fork()) {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                /*jesli uzytkownik nie podal programu zostaje uzyte echo, w przeciwnym wypadku uruchamiany jest wskazany program*/
                if (argc < 2) {
                    sprintf(output_msg, "%s", get_pids());
                    exec_program("echo", "echo", output_msg);
                } else {
                    sprintf(output_msg, "%s", get_pids());
                    exec_program(program_path, argv[1], output_msg);
                }
                break;
            default:
                if (wait(NULL)==-1) {
                    perror("wait error");
                    exit(1);
                }
                break;
        }
    }
    return 0;
}
