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

//---
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MAXNITEMS 1000000
#define MAXNTHREADS 100


/* globali condivise dai thread */

int nitems;
int buff[MAXNITEMS];

struct {
    pthread_mutex_t mutex;
    int nput; // indice successivo in cui memorizzare
    int nval; // valore successivo da memorizzare
} put = {PTHREAD_MUTEX_INITIALIZER}; // assegna alla prima il valore

struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int nready; // numero a disposizione del consumatore
} nready = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER }; // assegna alle prime 2 il valore

/* fine globali */

void * produce(void * arg) {
    while (1) {
        pthread_mutex_lock( & put.mutex); // blocca il mutex
        if (put.nput >= nitems) { 
            pthread_mutex_unlock( & put.mutex); // se non necessita produrre più (array pieno) unlock mutex
            return (NULL);
        }
        buff[put.nput] = put.nval; // assegna buff[i]=i
        put.nput++;
        put.nval++;
        pthread_mutex_unlock( & put.mutex); // unlock mutex

        pthread_mutex_lock( & nready.mutex); // blocca il mutex2
        if (nready.nready == 0)
            pthread_cond_signal( & nready.cond); // esegue una signal alla varibile di condizione che attiva il consumatore, (che sta a 0)
        nready.nready++; // dice che può proseguire al consumatore a consumare
        pthread_mutex_unlock( & nready.mutex); // sblocca il mutex2

        *((int * ) arg) += 1;
    }
}

//---

void * consume(void * arg) {
    int i;
    for (i = 0; i < nitems; i++) {
        pthread_mutex_lock( & nready.mutex); //blocca il mutex2
        if (nready.nready == 0)
            pthread_cond_wait( & nready.cond, & nready.mutex); // se non è disp niente aspetta la condizione e il mutex2 sbloccato
        nready.nready--; // consuma
        pthread_mutex_unlock( & nready.mutex); // sblocca il mutex2
        if (buff[i] != i) //esegue il controllo
            printf("buff[%d] = %d\n", i, buff[i]);
    }
    return (NULL);
}

//---

int main(int argc, char ** argv) {
    int i, nthreads, count[MAXNTHREADS];
    pthread_t tid_produce[MAXNTHREADS], tid_consume;
    if (argc != 3) {
        printf("usage: prodcons3 <#items> <#threads>");
        exit(-1);
    }
    nitems = MIN(atoi(argv[1]), MAXNITEMS);
    nthreads = MIN(atoi(argv[2]), MAXNTHREADS);
    /* crea tutti i produttori ed un consumatore */
    for (i = 0; i < nthreads; i++) {
        count[i] = 0;
        pthread_create( & tid_produce[i], NULL, produce, & count[i]);
    }
    pthread_create( & tid_consume, NULL, consume, NULL);
    /* aspetta tutti i produttori ed il consumatore */
    for (i = 0; i < nthreads; i++) {
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }
    pthread_join(tid_consume, NULL);
    exit(0);
}
