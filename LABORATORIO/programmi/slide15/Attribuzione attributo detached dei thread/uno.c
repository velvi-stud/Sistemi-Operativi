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

int makethread( void*(*fn) (void *), void *arg) {
    int err;
    pthread_t tid;
    pthread_attr_t attr;

    // inizializzazione della struttura attr -> per gli argomenti
    err = pthread_attr_init( & attr);
    if (err != 0)
        return (err);

    // poi facciamo il set dello stato discattato del thread
    err = pthread_attr_setdetachstate( & attr, PTHREAD_CREATE_DETACHED);
    if (err == 0)
        // ora il secondo argomento passato è &attr
        err = pthread_create( & tid, & attr, fn, arg);
    // alla fine del thread distruggo la struttura passata nel secondo argomento
    pthread_attr_destroy( & attr);

    return (err);
}
