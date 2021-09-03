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

//SERVER    

int main() {
    int server_sockfd;
    int client_sockfd;

    int server_len;
    int client_len;
    
    /* poichè utilizza protocolli tcp/ip si usa una struct sockaddr_in (rete -> TCP/IP AF_INET) invece di sockaddr_un (locale -> LOCAL AF_UNIX) */
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    /* crea un socket senza nome per il server */
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* assegna un nome alla socket */
    server_address.sin_family = AF_INET;
    // Non funziona con inet_addr("127.0.0.1");
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // si connette ad un indirizzo ip (in questo caso simula il locale), si noti che inet_addr serve per convertire una stringa in ip
    server_address.sin_port = htons(1313); // si connette ad una porta non utilizzata da standard
    server_len = sizeof(server_address);

    /* provvede a personalizzarla*/
    bind(server_sockfd, (struct sockaddr*) &server_address, server_len);

    /* creiamo una coda di connessione ed attendiamo i client (max 5 paralleli) */
    listen(server_sockfd, 5);

    while (1) { // resta sempre attivo per ricevere messaggi
        char ch;
        printf("server in attesa \n");

        /* accetta una connessione */
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_address, &client_len);

        /* Leggiamo e scriviamo al client su client_sockfd */
        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}
