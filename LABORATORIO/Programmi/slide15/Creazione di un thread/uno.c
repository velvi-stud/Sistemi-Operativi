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

// la variabile che identifica il thread
pthread_t ntid;

void printids(const char *s) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf(" %s pid %lu tid %lu(0x%lx)\n", s, (unsigned long) pid, (unsigned long) tid, (unsigned long) tid);
}

void *thr_fn (void *arg) {
    printids("nuovo thread: ");
    return (void*)0;
}

int main(void) {
    // gli passo la variabile che identifica il thread(global) ->ntid, poichè ha attributi di default -> NULL, la funzione che deve essere eseguita -> thr_fn, poichè non prende nessun argomento -> NULL
    int err = pthread_create( &ntid, NULL, thr_fn, NULL);
    if (err != 0) {
        fprintf(stderr, "non posso creare il thread: %s\n", strerror(err));
        exit(1);
    }
    printids("thread principale: ");
    sleep(1);
    exit(0);
}
