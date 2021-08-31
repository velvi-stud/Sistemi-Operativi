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

#define FIFO_NAME "/tmp/my_fifo" 
#define OPEN_MODE O_RDONLY

#define BUFFER_SIZE PIPE_BUF //ATTENZIONE UNA PIPE HA UNA PROPRIA GRANDEZZA DI TRASMISSIONE MASSIMA IDENTIFICATA DA PIPE_BUF (in questo caso 4096)

//CONSUMATORE -> processo 2 legge ed elimina i dati dalla FIFO

int main(){ 


int res;
printf("Processo: %d apre FIFO %d (O_RDONLY)\n", getpid(),OPEN_MODE);
int pipe_fd = open(FIFO_NAME, OPEN_MODE);
printf("Processo %d fd fifo: %d\n", getpid(), pipe_fd);

int i=0;
char buffer[BUFFER_SIZE];
int bytes_read = 0;

if (pipe_fd != -1) { // fifo aperta con successo se 1= -1
    do {
        printf("RICHIESTA: %d -> ",++i);
        res = read(pipe_fd, buffer, BUFFER_SIZE); //legge dalla fifo, passa ciò che ha letto nel buffer di lunghezza pari a BUFFER_SIZE
        printf("LETTURA: %s\n",buffer);
        bytes_read += res;
    } while (res > 0); //continua finchè ci sono ancora byte da leggere
    close(pipe_fd);
} 
else {
    exit(-1);
}
printf("Processo: %d finito, sono stati letti: %d bytes\n", getpid(), bytes_read);
exit(0);
}
