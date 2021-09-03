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
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// CLIENT    

int main() {
chdir("../"); // si posizionano nella sopracartella comune per poter utilizzare entrambi le socket in comune

    int sockfd; // file descriptor della socket
    int len;
 
    struct sockaddr_un address; 

    int result; // risultato operazione del server
    char ch = 'A'; // input al server

    /* creiamo una socket per il client */
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    /* definiamo le generalità della socket del server */
    address.sun_family = AF_UNIX; // tipo -> usando una struct sockaddr_un è logico che sia AF_UNIX
    strcpy(address.sun_path, "./server_socket"); // nome della socket che si utilizza per la connessione al server, ovviamente il server deve avere lo stesso
    len = sizeof(address); // size dell'address compilato

    /* connettiamo la nostra socket con quella del server e controlla la connessionee*/
    result = connect(sockfd, (struct sockaddr*) &address, len); // DA NOTARE che si usa (struct sockaddr * ) & address per rendere compatibile il tipo passato, essendo address un struct sockaddr_un per essere tipo sockaddr (anche avendo gli stessi campi)
    if (result == -1) {
        perror("ops: client 1");
        exit(1);
    }

    /* possiamo leggere e scrivere via sockfd */
    write(sockfd, & ch, 1); // scrive solo un carattere
    read(sockfd, & ch, 1); // legge il carattere elaborato dal server, lo scopo del server è cambiare il carattere con quello dopo.
    printf("char dal server = %c \n", ch); // stampa risultato dell'output del server
    close(sockfd); // chiude la socket aperta sul fd sockfd
    exit(0); // esce
}




