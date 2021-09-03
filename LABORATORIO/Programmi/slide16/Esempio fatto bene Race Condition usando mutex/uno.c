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

int myglobal; // --------> oggetto per la race condition 

//inizializza il mutex
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER; 

//funzione per il thread
void * thread_function(void * arg) {
    int j;
    // threads-> esegue le operazioni
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock( & mymutex); // lock il mutex
        j = myglobal;
        j = j + 1;
        printf(".");
        fflush(stdout);
        sleep(1);
        myglobal = j;
        pthread_mutex_unlock( & mymutex); // unlock mutex
    }
    return NULL;
}


int main(void) {

    // crea un nuovo thread
    pthread_t mythread;
    if (pthread_create( & mythread, NULL, thread_function, NULL)) {
        printf("creazione del thread fallita.");
        exit(1);
    }
    
    // main-> esegue le operazioni
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock( & mymutex); // lock mutex
        myglobal = myglobal + 1;
        pthread_mutex_unlock( & mymutex); // unlock mutex
        printf("o");
        fflush(stdout);
        sleep(1);
    }
    
    // aspetta che il thread finisca
    if (pthread_join(mythread, NULL)) {
        printf("errore nel join con il thread.\n");
        exit(2);
    }
    
    //stampo il risultato
    printf("\nmyglobal è uguale a %d\n", myglobal);
    exit(0);
}

