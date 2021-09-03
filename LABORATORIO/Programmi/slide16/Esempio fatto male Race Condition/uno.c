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


int myglobal; // variabile globale int 

// funzione riservata al thread
void * thread_function(void * arg) {
    int j;
    for (int i = 0; i < 20; i++) {
        j = myglobal;
        j = j + 1;
        printf("."); fflush(stdout);
        sleep(1);
        myglobal = j;
    }
    return NULL;
}


int main(void) {
 
    // creo thread
    pthread_t mythread;
    if (pthread_create( & mythread, NULL, thread_function, NULL)) {
        printf("creazione del thread fallita.\n");
        exit(1);
    }
    // processo main
    for (int i = 0; i < 20; i++) {
        myglobal = myglobal + 1;
        printf("o");fflush(stdout);
        sleep(1);
    }
    //aspetto finisca il thread
    if (pthread_join(mythread, NULL)) {
        printf("errore nel join dei thread.");
        exit(2);
    }
    // stampo risultato
    printf("\nmyglobal e’ uguale a %d\n", myglobal);
    exit(0);
}


