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


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MAXNITEMS 1000000
#define MAXNTHREADS 100

int nitems; //sola lettura per prod. e cons.
struct {
    pthread_mutex_t mutex;
    int buff[MAXNITEMS];
    int nput;
    int nval;
} shared = { PTHREAD_MUTEX_INITIALIZER }; // si noti che l'assegnazione della variabile mutex è andata alla struttura per il primo argomento

//---




//---

void * produce(void * arg) {
    for (;;) {
        pthread_mutex_lock( & shared.mutex);
        if (shared.nput >= nitems) {
            pthread_mutex_unlock( & shared.mutex);
            return (NULL); /* array pieno */
        }
        shared.buff[shared.nput] = shared.nval; //assegna a  buff[i] == i
        shared.nput++;
        shared.nval++;
        pthread_mutex_unlock( & shared.mutex);
        *((int * ) arg) += 1;
    }
}


//---

void consume_wait(int i) { // questa funzione aspetta che l'iesimo elemento sia stato instanziato
    for (;;) {
        pthread_mutex_lock( & shared.mutex);
        if (i < shared.nput) {
            pthread_mutex_unlock( & shared.mutex);
            return; /* un elemento è pronto */
        }
        pthread_mutex_unlock( &shared.mutex);
    }
}

void * consume(void * arg) { // controlla che buff[i] == i, altrimenti lo stampa
    int i;
    for (i = 0; i < nitems; i++) {
        consume_wait(i); // adesso esegue la funzione consume_wait();
        if (shared.buff[i] != i)
            printf("buff[%d] = %d\n", i, shared.buff[i]); // non dovrebbe stampare poichè sono tutti corretti
    }
    return (NULL);
}

//---



int main(int argc, char ** argv) {

    int i;
    int nthreads;
    int count[MAXNTHREADS];

    pthread_t tid_produce[MAXNTHREADS];
    pthread_t tid_consume;

    if (argc != 3) {
        printf("usage: prodcons2 <#items> <#threads>");
        exit(-1);
    }
    nitems = MIN(atoi(argv[1]), MAXNITEMS);
    nthreads = MIN(atoi(argv[2]), MAXNTHREADS);

    for (i = 0; i < nthreads; i++) {
        count[i] = 0;
        pthread_create( & tid_produce[i], NULL, produce, & count[i]);// crea i produttori
    }

    pthread_create( &tid_consume, NULL, consume, NULL); //crea il consumatore

    /* aspetta tutti i produttori e il consumatore */
    for (i = 0; i < nthreads; i++) {
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }
    pthread_join(tid_consume, NULL);

//esce
    exit(0);
}

