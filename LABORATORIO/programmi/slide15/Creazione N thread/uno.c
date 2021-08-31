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

// numero di thread che voglio eseguire
#define NUM_THREADS 8

/* Questa routine riceve in ingresso l'id del thread */
void * PrintHello(void * threadid) {
    int * id_ptr, taskid;
    sleep(1);
    id_ptr = (int * ) threadid;
    taskid = * id_ptr;
    printf("Thread %d\n", taskid);
    pthread_exit(NULL);
}

/* sbagliato
int main(int argc, char * argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc, t;
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %d\n", t);
        rc = pthread_create( & threads[t], NULL, PrintHello, (void * ) & t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
*/

/*corretto*/
int main(int argc, char *argv[]) {
    //array di N per gli id thread
    pthread_t threads[NUM_THREADS];
    // array di puntatori di N elementi
    int *taskids[NUM_THREADS];
    //variabili di controllo e di assegnazione
    int rc, t;
    for (t = 0; t < NUM_THREADS; t++) {
        // esegua la malloc per gestire l'indipendenza dei threadd
        taskids[t] = (int *) malloc(sizeof(int)); /* indirizzo di un intero */
        * taskids[t] = t; /* l'intero */
        printf("Creating thread %d\n", t);
        rc = pthread_create( & threads[t], NULL, PrintHello, (void *) taskids[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

