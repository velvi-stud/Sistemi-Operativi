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


#define SEM_LEGGI "/leggi"
#define SEM_SCRIVI "/scrivi"

int n;

struct { // dati condivisi da main, prod. e cons.
    int var;
    sem_t * leggi; // critic section -> read shinc.
    sem_t * scrivi; // critic section -> write shinc.
} 
shared;

    
void *reader(void *arg) {
    for (int i = 0; i < n; i++) { 
        sem_wait(shared.leggi); // attende 
        printf("figlio legge: %d\n",shared.var);
        sem_post(shared.scrivi);//esegue una signal su che indica che un processo che sta aspettando (wait) venga sbloccato
    }
}

void *writer(void *arg) {
    for (int i = 0; i < n; i++) { 
        sem_wait(shared.scrivi);
        shared.var= shared.var+1;
        printf("padre scrive: %d\n",shared.var);
        sem_post(shared.leggi);//esegue una signal su che indica che un processo che sta aspettando (wait) venga sbloccato
    }
}


/**/
int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("usage: prodcons1 <#items>");
        exit(-1);
    }
    n = atoi(argv[1]);
    
    /* crea il semafori (variabile shared)*/
    shared.leggi = sem_open(SEM_LEGGI, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0); // critic section -> insert and remove from buff
    shared.scrivi = sem_open(SEM_SCRIVI, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1); // critic section -> insert and remove from buff
    shared.var=0;
    
    /* crea i due thread */
    pthread_t child, father;
    pthread_create( &father, NULL, reader, NULL); // thread produttore
    pthread_create( &child, NULL, writer, NULL); // thread produttore
    
    pthread_join(child, NULL);
    pthread_join(father, NULL);
    
    /*chiude e rimuove il semaforo */
    sem_close(shared.leggi);
    sem_unlink(SEM_LEGGI);
    sem_close(shared.scrivi);
    sem_unlink(SEM_SCRIVI);
    exit(0);
}

/**/
