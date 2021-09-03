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

//CLIENT

int main() {

    int sockfd;
    int len;

    struct sockaddr_in address;

    int result;
    char ch = 'A';

    /* creiamo una socket per il client */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* assegnamo le caratteristiche che deve avere la socket che si vuole usare per la connessione di proprietà del server */
    address.sin_family = AF_INET;
    // Non funziona con inet_addr("127.0.0.1");
    address.sin_addr.s_addr = htonl(INADDR_ANY); //si noti che inet_addr serve per convertire una stringa in ip
    address.sin_port = htons(1313); //serve per settare bene la porta
    len = sizeof(address);

    /* connettiamo la nostra socket con quella del server e la controlla */
    result = connect(sockfd, (struct sockaddr*) &address, len);
    if (result == -1) {
        perror("ops: client 1");
        exit(1);
    }

    /* possiamo leggere e scrivere via sockfd */
    write(sockfd, & ch, 1);
    read(sockfd, & ch, 1);
    printf("char dal server = %c \n", ch);
    close(sockfd);
    exit(0);
}
