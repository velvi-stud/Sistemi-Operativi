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

// funzione primo thread
void *thread1 (void *arg) {
    int *error = (int *) arg;
    printf("Sono il primo thread. Parametro = %d\n", *(int*) arg);
    pthread_exit( (void *) error);
}

// funzione secondo thread
void *thread2 (void *arg) {
    int error =  *(int*)(arg);
    printf("Sono il secondo thread. Parametro = %d\n", error);
    pthread_exit( (void *) &error);
}

int main() {


    pthread_t th1, th2;// var per i thread
    int i1 = 1, i2 = 2;//argomenti da passare ai thread
    void * uscita;// valore di ritorno dai thread

// creiamo i rispettivi processi thread con gli argomenti passati
    pthread_create( &th1, NULL, thread1, (void *) &i1);
    pthread_create( &th2, NULL, thread2, (void *) &i2);

// aspetta che termini il primo thread
    pthread_join(th1, &uscita);
    printf("t1->stato = %d\n", *(int *) uscita);

// aspetta che termini il secondo thread
    pthread_join(th2, &uscita);
    printf("t2->stato = %d\n", *(int *) uscita);

// terminazione programma
    exit(0);
}
