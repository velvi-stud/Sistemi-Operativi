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
#define OPEN_MODE O_WRONLY

#define BUFFER_SIZE PIPE_BUF //ATTENZIONE UNA PIPE HA UNA PROPRIA GRANDEZZA DI TRASMISSIONE MASSIMA IDENTIFICATA DA PIPE_BUF (in questo caso 4096)
#define TEN_MEG (1024 * 1000 * 10) // quantità massima di dati da produrre


//PRODUTTORE-> crea una FIFO (bloccante) se richiesto, poi vi scrive i dati quanto prima.

int main(){

int res;

/* se nel caso dovesse trasferire un file txt tramite pipe tra processi
int fd_text = open("./testo.txt",O_RDONLY);
read(fd_text,buffer,BUFFER_SIZE);
*/

if (access(FIFO_NAME, F_OK) == -1){ // controlla se non esiste, in tal caso la crea
    res = mkfifo(FIFO_NAME, 0777);  // crea la fifo con tutti i permessi garantiti
    if (res != 0) {
        printf("Errore creazione FIFO: %s\n", FIFO_NAME);
        exit(-1);
    }
}

printf("Processo: %d apre FIFO in modalita: %d (O_WRONLY)\n", getpid(),OPEN_MODE);
int pipe_fd = open(FIFO_NAME, OPEN_MODE); //come ogni altra open viene aperta su un file descriptor
printf("Processo: %d fd fifo: %d\n", getpid(), pipe_fd);

// variabili usate per la comunicazione
int i=0;
int bytes_sent = 0;
char buffer[BUFFER_SIZE]="Inviato dal produttore <3";

if (pipe_fd != -1) { //la pipe è aperta con successo
    while (bytes_sent < TEN_MEG) { //quindi invia 2500 volte il buffer per eguagliare il TEN_MEG -> come se fosse la quantità massima prodotta
        printf("DOMANDA: %d\n",++i);
        res = write(pipe_fd, buffer, BUFFER_SIZE);
        if (res == -1) {
            printf("Errore lettura fifo\n");
            exit(1);
        }
        bytes_sent += res;
    }
    close(pipe_fd);
} 
else {
    printf("Errore apertura FIFO: %s\n", FIFO_NAME);
    exit(1);
}
printf("Processo: %d finisce\n", getpid());
exit(1);
}
