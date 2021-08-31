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


#define NBUFF 10
#define SEM_MUTEX "/mutex"
#define SEM_NEMPTY "/nempty"
#define SEM_NSTORED "/nstored"

int nitems; // sola lettura per prod. e cons. 

struct { // dati condivisi da main, prod. e cons.
    int buff[NBUFF];
    sem_t * mutex; // critic section -> insert and remove from buff
    sem_t * nempty; // count void location
    sem_t * nstored; // count occuped location
}
shared; 
/**/


/**/
void * produce(void * arg) {
    for (int i = 0; i < nitems; i++) { //esegue operazioni sul buffer circolare pari all'inserimento e consuma di nitems oggetti
    
        sem_wait(shared.nempty); // attende almeno un posto vuoto
        
        sem_wait(shared.mutex); // se ha ottenuto il posto vuoro, entra nella sezione critica bloccando il mutex
        shared.buff[i % NBUFF] = i; // inserisce l'elemento nel buffer circolare
        sem_post(shared.mutex); // chiude la sezione critica
        
        sem_post(shared.nstored);//esegue una signal su nstored che indica che un thread aspettando un campo pieno (wait) venga sbloccato poichè è stato riempito
    }
    return (NULL);
}


/**/
void * consume(void * arg) {
    int i;
    for (i = 0; i < nitems; i++) { //esegue operazioni sul buffer circolare pari all'inserimento e consuma di nitems oggetti
    
        sem_wait(shared.nstored); // attende che ci sia una signal che mi sblocchi, indicando che posso procedere a prendere un elemento
        
        sem_wait(shared.mutex); // una volta ottenuto la wait posso procedere bloccando il mutex per "consumare" un elemento nel buffer circolare
        if (shared.buff[i % NBUFF] != i) 
            printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
        sem_post(shared.mutex); // chiudo la sezione critica
        
        sem_post(shared.nempty); // do il via tramite la post al processo produttore di produrre (aka. c'è un posto libero)
    }
    return (NULL);
}


/**/
int main(int argc, char ** argv) {

    if (argc != 2) {
        printf("usage: prodcons1 <#items>");
        exit(-1);
    }
    nitems = atoi(argv[1]);
    
    /* crea i tre semafori */
    shared.mutex = sem_open(SEM_MUTEX, O_CREAT | O_EXCL, FILE_MODE, 1); // critic section -> insert and remove from buff
    shared.nempty = sem_open(SEM_NEMPTY, O_CREAT | O_EXCL, FILE_MODE, NBUFF); // count void location
    shared.nstored = sem_open(SEM_NSTORED, O_CREAT | O_EXCL, FILE_MODE, 0); // count occuped location
    
    /* crea un thread produttore ed un thread consumatore */
    pthread_t tid_produce,tid_consume;
    pthread_create( & tid_produce, NULL, produce, NULL); // thread produttore
    pthread_create( & tid_consume, NULL, consume, NULL); //thread consumatore
    
    /* attende i due thread finiscano*/
    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);
    
    /*chiude e rimuove i semafori */
    sem_close(shared.mutex);
    sem_close(shared.nempty);
    sem_close(shared.nstored);
    sem_unlink(SEM_MUTEX);
    sem_unlink(SEM_NEMPTY);
    sem_unlink(SEM_NSTORED);
    
    exit(0);
}

/**/
