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
#include <ctype.h>
//#include "client.h"


#define SERVER_FIFO_NAME "/tmp/serv_fifo"
#define CLIENT_FIFO_NAME "/tmp/cli_%d_fifo"
#define BUFFER_SIZE 40
struct data_to_pass_st {
    pid_t client_pid;
    char some_data[BUFFER_SIZE];
};



int main() {
    int server_fifo_fd;
    int client_fifo_fd;

    struct data_to_pass_st my_data; // struttura da leggere e restituire

    int read_res;
    char client_fifo[256]; // per il nome della FIFO del client
    char * tmp_char_ptr;

    //creo e apro la fifo del server
    mkfifo(SERVER_FIFO_NAME, 0777);
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY); // dalla sua FIFO leggerà solo (poichè deve aspettare le connessioni), da quella del client scriverà solo
    if (server_fifo_fd == -1) {
        printf("Server fifo failure\n");
        exit(1);
    }

    printf("\nattendo 10 sec\n");
    sleep(10); // accodiamo i client per scopi dimostrativi
    do {
        read_res = read(server_fifo_fd, &my_data, sizeof(my_data)); /*controlla se riceve qualche messaggio dai client sulla sua fifo. Se dovesse riceverlo allora poichè il protocollo di comunicazione si basa sullo standard formato dalla sola struct data_to_pass_st allora leggo la pipe e la passo in una variabile my_data dello stesso tipo*/
        
        if (read_res > 0){ // se li riceve allora esegue...

            /* In questa prossima fase, eseguiamo qualche operazione sui dati appena letti dal client. 
            Il servizio che esegue il server sta nel convertire tutti i caratteri in lettere maiuscole e combiniamo il CLIENT_FIFO_NAME con il pid del client ricevuto. */

            tmp_char_ptr = my_data.some_data; // salva il messaggio inviato dal cliente situato nella struct my_data.some_data nella variabile tmp_char_ptr in modo da poterla manipolare successivamente.
            while ( * tmp_char_ptr) { // questo ciclo prende ogni carattere della sringa e lo rende maiuscolo
                * tmp_char_ptr = toupper( * tmp_char_ptr);
                tmp_char_ptr++;
            }
            sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid); /* modifico il %d in  *#define CLIENT_FIFO_NAME "/tmp/cli_%d_fifo"* creando una nuova fifo a seconda del pid dei processi client esempio se il pid di questo processo è 555 la relativa fifo creata sarà in /tmp/cli_555_fifo */
            client_fifo_fd = open(client_fifo, O_WRONLY); // apro la fifo personale del processo cliente
            if (client_fifo_fd != -1) { // se non ci sono errori d'apertura
                write(client_fifo_fd, & my_data, sizeof(my_data)); // gli scrivo la struct modificata 
                close(client_fifo_fd); // chiudo la fifo personale del processo
            }
        }
        
    }while (read_res > 0); // eseguo il ciclo fin quando ci sono write alla fifo del server (ma nel processo client)

    close(server_fifo_fd); // chiudo la fifo del server
    unlink(SERVER_FIFO_NAME); // elimino la fifo del server tramite l'unlink
    exit(0); //esco
}







