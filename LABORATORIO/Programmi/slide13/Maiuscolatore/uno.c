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
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#define SERVER_PORT 1313
#define LINESIZE 80

/* upperserver.c: un server per rendere maiuscole linee di testo */
//utilizziamo 2 socket, una per la connessione client-server un'altra per la server-client (risposta)
void upperlines(int in , int out) {
    char inputline[LINESIZE];
    int len, i;
    while ((len = recv( in , inputline, LINESIZE, 0)) > 0) {
        for (i = 0; i < len; i++)
            inputline[i] = toupper(inputline[i]);
        send(out, inputline, len, 0);
    }
}

int main(int argc, char ** argv) {
    int sock, client_len, fd;
    struct sockaddr_in server;
    struct sockaddr_in client;

    /* impostazione dell’end point della comunicazione */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("chiamata alla system call socket fallita");
        exit(1);
    }
    /* personalizzo la sock del server */
    server.sin_family = AF_INET;
    /* si usa htonl e htons per identificare esattamente i byte ip e server per un controllo migliore della connessione */
    server.sin_addr.s_addr = htonl(INADDR_ANY); //abilita connessione a qualsiasi indirizzo ip
    server.sin_port = htons(SERVER_PORT); 

    /* leghiamo l'indirizzo all’end point della comunicazione */
    if (bind(sock, (struct sockaddr*) &server, sizeof server) == -1) {
        perror("chiamata alla system call bind fallita");
        exit(2);
    }
    
    /* si mette in attesa, solo 1 processo per volta*/
    listen(sock, 1);
    /* gestione delle connessioni dei client */
    while (1) {
        client_len = sizeof(client);
        /* accetta e controlla la connessione del client in uscita */
        if ((fd = accept(sock, (struct sockaddr*) &client, &client_len)) < 0) {
            perror("accepting connection");
            exit(3);
        }
        fprintf(stdout, "Aperta connessione.\n");
        send(fd, "Benvenuto all'UpperServer!\n", 27, 0);
        upperlines(fd, fd);
        close(fd);
        fprintf(stdout, "Chiusa connessione.\n");
    }
}
