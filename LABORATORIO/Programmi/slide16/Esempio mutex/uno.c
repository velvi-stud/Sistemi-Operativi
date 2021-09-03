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

#define MAX 10

pthread_mutex_t M; /* def.mutex condiviso tra thread */

int DATA = 0; /* variabile condivisa */

int accessi1 = 0; // num. accessi thread 1 alla sez. critica 
int accessi2 = 0; // num. accessi thread 2 alla sez. critica 

void  *thread1_process(void * arg) {
    int k = 1;
    while (k) {
        accessi1++;
        pthread_mutex_lock(&M); // blocca il mutex
        DATA++;
        k = (DATA >= MAX ? 0 : 1);
        pthread_mutex_unlock(&M); // sblocca il mutex
    
        printf("accessi di T1: %d\n", accessi1);
        sleep(1);
    }
    pthread_exit(0);
}


void * thread2_process(void * arg) {
    int k = 1;
    while (k) {
        accessi2++;
        pthread_mutex_lock(&M); // blocca il mutex
        DATA++;
        k = (DATA >= MAX ? 0 : 1);
        pthread_mutex_unlock( & M); // sblocca il mutex
    
        printf("accessi di T2: %d\n", accessi2);
        sleep(1);
    }
    pthread_exit(0);
}



int main() {

    // il mutex è inizialmente libero 
    pthread_mutex_init (&M, NULL);

    // crea il thread 1
    pthread_t th1; 
    if (pthread_create( & th1, NULL, thread1_process, NULL) < 0) {
        fprintf(stderr, "errore creazione per thread 1\n");
        exit(1);
    }

    // crea il thread 2
    pthread_t th2; 
    if (pthread_create( & th2, NULL, thread2_process, NULL) < 0) {
        fprintf(stderr, "errore creazione per thread 2\n");
        exit(1);
    }
    
    //aspetta finiscano entrambi thread
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    // stampa il numero di accessi alla var glob e il valore di DATA -> si ricorda che gli accessi alla variabile sono massimo 10 (indipend. dal thread accedente)
    printf("Accessi: T1: %d, T2 %d\n", accessi1, accessi2);
    printf("Totale accessi: %d\n", DATA);

    //esce
    exit(0);
}
