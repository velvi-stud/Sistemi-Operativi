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


pthread_once_t init = PTHREAD_ONCE_INIT;

void init_funz() {
    //varie inizializzazioni… 
    printf(“inizializzazione effettuata\ n”);
}

void *funzione(void *arg) {
    pthread_once( &init, init_funz);
    //…istruzioni 
    printf(“funzione\ n”);
}

int main() {
    pthread_t t1, t2; // attributi
    int r1, r2; // stato di creazione
    r1 = pthread_create( &t1, NULL, funzione, NULL);
    r2 = pthread_create( &t2, NULL, funzione, NULL);
}
