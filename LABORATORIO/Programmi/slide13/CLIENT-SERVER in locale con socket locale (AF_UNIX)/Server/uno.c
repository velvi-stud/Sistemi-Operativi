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

// SERVER

int main() {
chdir("../"); // si posizionano nella sopracartella comune per poter utilizzare entrambi le socket in comune

    int server_sockfd;
    int client_sockfd;

    int server_len; 
    int client_len;

    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    /* Rimuoviamo eventuali vecchie socket e creiamo una socket senza nome per il server */
    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0); // crea una nuova socket generica

    /* Assegnamo un nome alla socket */
    server_address.sun_family = AF_UNIX; // setta il tipo -> logia sia AF_UNIX se usiamo la struct sockaddr_un
    strcpy(server_address.sun_path, "./server_socket"); // setta il nome della socket, ovviamente chi si vuole connettere deve avere lo stesso nome.
    server_len = sizeof(server_address); // prende il size dell'indirizzo calcolato
    bind(server_sockfd, (struct sockaddr * ) & server_address, server_len); // assegnamo il nome alla socket, indirizzo e size. (bind -> legare)

    /* creiamo una coda di connessione ed attendiamo i client possono esserci solo 5 processi in contemporanea*/
    listen(server_sockfd, 5);
    while (1) {
        char ch;
        printf("server in attesa \n");

        /* accetta una connessione */
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr * ) & client_address, & client_len); /* accetta la connessione proveniente dalla socket server_sockfd, e utilizza i canale di comunicazione client_address avente lunghezza client_len per connettersi e "parlare" con il client */

        /* Leggiamo e scriviamo al client su client_sockfd */
        read(client_sockfd, & ch, 1); // legge cosa gli ha inviato il client (un solo carattere)
        ch++; // modifica il carattere
        write(client_sockfd, & ch, 1); // scrive il carattere modificato
        close(client_sockfd); // chiude la socket aperta per il client
    }
}



