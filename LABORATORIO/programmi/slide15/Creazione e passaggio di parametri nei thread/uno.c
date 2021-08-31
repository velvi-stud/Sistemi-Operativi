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
#include <pthread.h>

/* parametri per char_print -> sarà il tipo dell'argomento passato dai thread */
struct char_print_parms {
    char character;
    int count;
};

/* funzione che sarà eseguita dai thread */
void *char_print (void* parameters) { //instanziamo a void i parametri in quanto il tipo andrà definito nella struttura della function
    struct char_print_parms *p = (struct char_print_parms*) parameters;  /* cast del puntatore al tipo corretto */
    for (int i = 0; i < p -> count; ++i)
        fputc(p->character, stderr);
    return NULL;
}

int main() {

    /* variabili identificative thread */
    pthread_t tid1;
    pthread_t tid2;
    /* poichè i dati possono essere passati tramite struct: */
    struct char_print_parms tid1_args;
    struct char_print_parms tid2_args;

    /* crea un thread per stampare 30000 ‘x’ */
    tid1_args.character = '0';
    tid1_args.count = 30000;
    pthread_create( &tid1 , NULL , char_print , (void*) &tid1_args); //notare il passaggio del parametro

    /* crea un thread per stampare 20000 ‘y’ */
    tid2_args.character = '1';
    tid2_args.count = 20000;
    pthread_create( &tid2 , NULL , char_print , (void*) &tid2_args); //notare il passaggio del parametro

    /* aspetta che i thread finiscano prima di chiudere il programma */
    // se dovesse chiudersi prima dell'esecuzione dei thread allora questi non verranno mai eseguiti
    sleep(1);
    return 0;
}
