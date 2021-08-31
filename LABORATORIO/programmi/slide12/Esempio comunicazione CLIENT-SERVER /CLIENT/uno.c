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
struct data_to_pass_st{
    pid_t client_pid;
    char some_data[BUFFER_SIZE];
};




int main() {
    int server_fifo_fd;
    int client_fifo_fd;

    struct data_to_pass_st my_data;
    char client_fifo[256];
    
    // apre la fifo che lo connette al server
    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (server_fifo_fd == -1) {
        fprintf(stderr, "Nessun server attivo al momento...\n");
        exit(1);
    }

    my_data.client_pid = getpid();
    sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid); /* modifico il %d in  *#define CLIENT_FIFO_NAME "/tmp/cli_%d_fifo"* creando una nuova fifo a seconda del pid dei processi client esempio se il pid di questo processo è 555 la relativa fifo creata sarà in /tmp/cli_555_fifo */
    if (mkfifo(client_fifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", client_fifo);
        exit(1);
    }

    /* I dati dei client sono inviati al server.
    Successivamente è aperta la FIFO client (sola lettura, modalità bloccante) ed i dati sono letti dal client.
    Infine, la FIFO del server è chiusa e la FIFO client rimossa dalla memoria. */

    sprintf(my_data.some_data, "Hello from %d", my_data.client_pid); // scrive nella struct nella sezione some_data la frase: "Hello dal processo 555" 
    printf("%d sent: %s, ", my_data.client_pid, my_data.some_data); // messaggio di controllo

    write(server_fifo_fd, &my_data, sizeof(my_data)); //scrive al server tutta la struct modificata del processo cliente poichè il protocollo di comunicazione avviene solo attraverso la struct data_to_pass_st, e pertanto si invia solo quella al serve.
    
    client_fifo_fd = open(client_fifo, O_RDONLY); //apre la sua fifo personale in lettura
    if (client_fifo_fd != -1) { // se l'apertura non ha generato errori
        if (read(client_fifo_fd, &my_data, sizeof(my_data)) > 0) /* si posiziona nella sua fifo personale aspettando che il processo server scriva qualcosa sulla fifo, in particolare il servizio del server si basa sul prende la frase scritta nella struct nella variabile some_data, portarla in maiuscolo e restituirgliela.*/
            printf("received: %s\n", my_data.some_data); // stampa il risultato ottenuto dalla read
        close(client_fifo_fd); //chiude la sua fifo aperta in lettura
    }
    close(server_fifo_fd); //chiude la fifo del server
    unlink(client_fifo); //elimina la fifo creata tramite l'unlink
    exit(0); // chiude il programma
}
