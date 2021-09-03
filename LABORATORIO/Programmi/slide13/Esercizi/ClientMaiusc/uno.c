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

#define IP_ADD INADDR_ANY
#define PORT 1313
#define LINESIZE 80

//CLIENT

int main(){

// creo canale di comunicazione socket avente come dominio un AF_INET (quindi da usare una struct sockaddr_in) e avente come protocollo SOCK_STREAM (TCP/IP)
int sockfd = socket(AF_INET,SOCK_STREAM,0);


//personalizzo la socket a cui mi voglio connettere
struct sockaddr_in address;
address.sin_family= AF_INET;
address.sin_addr.s_addr=htonl(IP_ADD);
address.sin_port=htons(PORT);
int len = sizeof(address);

//connettiamo le cartteristiche che la socket deve avere per connettersi al server
int try= connect(sockfd,(struct sockaddr*) &address, len);
if ( try == -1 ){
    perror("connessione alla socket del server fallita");
    exit(1);
}

char buffer[]="dovrebbe apparire maiuscolo";
// dovrebbe aspettare che il server gli dia il benvenuto (read e recv sono identiche al momento)
char welcome[LINESIZE];  read(sockfd, &welcome, LINESIZE);  printf("%s",welcome);
// gli invia il messaggio per l'elaborazione
send(sockfd,buffer,strlen(buffer),0);
// riceve il risultato dal server
recv(sockfd,buffer,strlen(buffer),0);
// si noti come la recv e read fanno le stesse cose
printf("\nsono il processo %d ed ho ricevuto: %s \n",getppid(),buffer);
exit(44);
}

