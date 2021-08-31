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

// funzione thread 1
void *thr_fn1(void * arg) {
    printf("thread 1 returning\n");
    return ((void *) 1);
}

// funzione thread 2
void *thr_fn2(void *arg) {
    printf("thread 2 exiting\n");
    pthread_exit((void *) 2);
}

int main(void) {

    int err; // per vedere lo stato di creazione del thread
    pthread_t tid1, tid2; // var identificativi per i thread

    void *tret; // var che memorizza il valore di uscita dei thread

    // crea il primo thread e controlla se tutto ok
    err = pthread_create( &tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        err_quit("can't create thread 1: %s\n", strerror(err));
    
    // crea il secondo thread e controlla se tutto ok
    err = pthread_create( &tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        err_quit("can't create thread 2: %s\n", strerror(err));

    // aspetta la fine del thread 1 e controlla se tutto ok
    err = pthread_join(tid1, &tret);
    if (err != 0)
        err_quit("can't join with thread 1: %s\n", strerror(err));
    printf("thread 1 exit code %ld\n", (long) tret); 

    // aspetta la fine del thread 2 e controlla se tutto ok
    err = pthread_join(tid2, &tret);
    if (err != 0)
        err_quit("can't join with thread 2: %s\n", strerror(err));
    printf("thread 2 exit code %ld\n", (long) tret);

    exit(0);
}
