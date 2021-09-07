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

//calcola i numeri primi
void * compute_prime(void * arg) {
    static int candidate = 2;
    int n = * ((int *) arg);
    int factor, is_prime;

    while (1) {
        is_prime = 1;
        for (factor = 2; factor <= candidate; ++factor)
            if (candidate % factor == 0) {
                is_prime = 0;
                break;
            }
        if (is_prime) {
            if (--n == 0)
                return (void *) &candidate;
        }
        ++candidate;
    }

    return NULL;
}


int main() {
    pthread_t tid; // var per thread
    int which_prime = 5000; // l'N-esimo numero primo
    void *prime; // var per il valore di ritorno del thread

    // assegno la funzione da eseguire al processo
    pthread_create( &tid, NULL, compute_prime, (void *) &which_prime);

    /* attende il calcolo del numero primo */
        pthread_join(tid, &prime); // e passa il valore di ritorno (5000-esimo numero primo) nella variabile prime
    printf("The %dth prime number is %d.\n", which_prime, *(int *) prime);
    
    // esce il programma    
    exit(0);
}



