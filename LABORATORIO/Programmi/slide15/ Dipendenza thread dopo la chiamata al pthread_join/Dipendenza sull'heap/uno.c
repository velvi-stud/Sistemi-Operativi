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


struct foo {
    int a, b, c, d;
};

// funzione generale di stampa della struttura
void printfoo(const char *s, const struct foo *fp) {
    printf("%s",s);
    printf("structure at 0x%lx\n",(unsigned long)fp); 
    printf("foo.a = %d\n", fp->a);
    printf(" foo.b = %d\n", fp->b); 
    printf(" foo.c = %d\n", fp->c); 
    printf("  foo.d = %d\n", fp->d);
}

// function thread 1
void * thr_fn1(void *arg) {
    struct foo *foo = malloc(sizeof(struct foo)); // alloco dinamicamente la struttura, così andrà memorizzata nell'heap sia la struttura che l'indirizzo
    foo->a=1;
    foo->b=2;
    foo->c=3;
    foo->d=4;

    printfoo("thread 1:\n", foo); 
    pthread_exit( (void *) foo); // ritorna la struttura modificata
}

// function thread 2
void * thr_fn2(void *arg){
    printf("thread 2: ID is %lu\n",(unsigned long)pthread_self());
    pthread_exit( (void *)0 ); // ritorna NULL
}

int main(void){
int err; // memorizza l'errore che causa
pthread_t tid1, tid2; // identifica i 2 threads
struct foo *fp; // variabile struttura che punta alla struttura ritornata dal thread 1

// crea ed assegna la function al processo
err = pthread_create(&tid1, NULL, thr_fn1, NULL); 
if (err != 0){
    printf("can't create thread 1: %s\n", strerror(err)); 
    exit(1);
} 

// aspetta la terminazione
err = pthread_join(tid1, (void *)&fp); // mi ritorna la struttra modificata sulla variabile fp
if (err != 0){
    printf("can't join with thread 1: %s\n",strerror(err)); 
    exit(1);
} 


// aspetta 1 sec. | che il thread finisce
sleep(1);

// il padre inizia un secondo thread
printf("parent starting second thread\n");

// crea un nuovo thread --> SOVRASCRIVE LO STACK DEL THREAD 1 MA NON L'HEAP
err = pthread_create(&tid2, NULL, thr_fn2, NULL); 
if (err != 0){
    printf("can't create thread 2: %s\n",strerror(err));
    exit(1);
}

// aspetta 1 sec | il tempo che finisce
sleep(1); 

// stampa la struct modificata dal thread 1 -> punta all'heap adesso
printfoo("parent:\n", fp); 

// termina
exit(0);
}

