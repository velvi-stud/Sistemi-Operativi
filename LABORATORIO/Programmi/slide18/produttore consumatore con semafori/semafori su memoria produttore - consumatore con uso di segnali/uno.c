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
#include <semaphore.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define NBUFF 10
#define MAXNTHREADS 100

int nitems, nproducers; // sola lettura per produttori e consumatore

struct { // dati condivisi da main, prod. e cons.
    int buff[NBUFF];
    int nput; // l’indice della prossima entrata del buffer in cui memorizzare (modulo NBUFF)
    int nputval; // il prossimo valore da memorizzare nel buffer
    /* semafori non puntatori */
    sem_t mutex; // critic section -> insert and remove from buff
    sem_t nempty; // count void location
    sem_t nstored; // count occuped location
}
shared;

/**/
void * produce(void * arg) {
    for (;;) {
        sem_wait( & shared.nempty); // aspetta almeno una locazione libera per poter inserire
        
        sem_wait( & shared.mutex); // attiva il mutex una volta che esiste un posto dove inserire 
        
        if (shared.nput >= nitems) { // se siamo arrivati al max numero di cose da produrre -> nu fa nient
            sem_post( & shared.nempty); // segnala che c'è un posto vuoto -> ovviamente anche gli altri thread produttori farannoquesto
            sem_post( & shared.mutex); // sblocca il mutex
            return (NULL); // tutto prodotto -> esci
        }
        shared.buff[shared.nput % NBUFF] = shared.nputval;
        shared.nput++;
        shared.nputval++;
        
        sem_post(&shared.mutex); // sblocca il mutex una volta eseguite le operazioni
        
        sem_post(&shared.nstored); // segnala l'inserimento di un nuovo elemento nell'array -> il consumatore può elaborare ora
        
        /* segnala che un altro elemento prodotto dal thread*/
        *((int*) arg) += 1;
    }
}
/**/

void * consume(void * arg) {
    int i;
    for (i = 0; i < nitems; i++) { //esegue operazioni sul buffer circolare pari all'inserimento e consuma di nitems oggetti
    
        sem_wait(&shared.nstored); // attende che ci sia una signal che mi sblocchi, indicando che posso procedere a prendere un elemento
        
        sem_wait(&shared.mutex); // una volta ottenuto la wait posso procedere bloccando il mutex per "consumare" un elemento nel buffer circolare
        if (shared.buff[i % NBUFF] != i) 
            printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
        sem_post(&shared.mutex); // chiudo la sezione critica
        
        sem_post(&shared.nempty); // do il via tramite la post al processo produttore di produrre (aka. c'è un posto libero)
    }
    return (NULL);
}
/**/

/**/
int main(int argc, char ** argv) {

    if (argc != 3) {
        printf("usage: prodcons3 <#items> <#producers>");
        exit(-1);
    }
    nitems = atoi(argv[1]);
    nproducers = MIN(atoi(argv[2]), MAXNTHREADS);
    int count[MAXNTHREADS];
    
    /* inizializza tre semafori */
    sem_init( & shared.mutex, 0, 1); // critic section -> insert and remove from buff
    sem_init( & shared.nempty, 0, NBUFF); // count void location
    sem_init( & shared.nstored, 0, 0); // count occuped location
    
    /* crea tutti i produttori ed un consumatore */
    pthread_t tid_produce[MAXNTHREADS]; // CI SONO PIÙ PROCESSI PRODUTTORI 
    pthread_t tid_consume; // MA SOLO UN PROCESSO CONSUMATORE
    for (int i = 0; i < nproducers; i++) {
        count[i] = 0;
        pthread_create( & tid_produce[i], NULL, produce, & count[i]);
    }
    pthread_create( & tid_consume, NULL, consume, NULL);
    
    /* aspetta tutti i produttori ed il consumatore -> stampa anche quante cose sono state prodotta da chi */
    for (int i = 0; i < nproducers; i++) {
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }
    pthread_join(tid_consume, NULL);
    
    /* chiude tutti i segnali */
    sem_destroy( & shared.mutex);
    sem_destroy( & shared.nempty);
    sem_destroy( & shared.nstored);
    exit(0);
}
