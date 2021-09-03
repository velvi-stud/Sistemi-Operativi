#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 
#include <sys/wait.h>
#include <math.h>
#include <signal.h>


#define FIFO_NAME "./my_fifo"
int main(int argc, char * argv[]) {
    int res;
    int open_mode = 0;
    int i;
    if (argc < 2) {
        printf("Uso: %s <combinazioni di O_RDONLY O_WRONLY O_NONBLOCK>\n", argv[0]);
        exit(1);
    }
    /* Impostiamo il valore di open_mode dagli argomenti. */
    /*Il programma ci consente di specificare da linea di comando la combinazione di O_RDONLY, O_WRONLY e O_NONBLOCK che vogliamo usare*/
    for (i = 1; i < argc; i++) {
        if (strncmp( * ++argv, "O_RDONLY", 8) == 0)
            open_mode |= O_RDONLY;
        if (strncmp( * argv, "O_WRONLY", 8) == 0)
            open_mode |= O_WRONLY;
        if (strncmp( * argv, "O_NONBLOCK", 10) == 0)
            open_mode |= O_NONBLOCK;
    }
    /* Se la FIFO non esiste la creiamo. Poi viene aperta */
    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            printf("Non posso creare la FIFO %s\n", FIFO_NAME);
            exit(1);
        }
    }
    
    printf("Processo %d apre la FIFO\n", getpid());
    res = open(FIFO_NAME, open_mode);
    printf("Risultato processo %d: %d\n", getpid(), res);
    sleep(5);
    if (res != -1)
        close(res);
    printf("Processo %d terminato\n", getpid());
    exit(0);
}
