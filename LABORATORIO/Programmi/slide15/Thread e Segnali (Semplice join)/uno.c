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

void * print_message_function(void * ptr) {
    char * message;
    message = (char *) ptr;
    printf("%s \n", message);
}

int main() {
    pthread_t thread1, thread2;
    char * message1 = "Thread 1";
    char * message2 = "Thread 2";
    int iret1, iret2;

    /* crea thread indipendenti, ciascuno dei quali eseguirà una funzione */
    iret1 = pthread_create( & thread1, NULL, print_message_function, (void *) message1);
    iret2 = pthread_create( & thread2, NULL, print_message_function, (void *) message2);

    /*aspetta che i thread abbiano completato prima che il main continui. 
    Se non aspettiamo si potrebbe eseguire una exit che terminerà l’intero processo e tutti i suoi thread, prima che questi abbiano finito */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    exit(0);
}


