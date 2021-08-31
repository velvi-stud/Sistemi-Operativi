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
#include <time.h>

int glob=0;

void *func(void *arg){
    int rnd= 1+rand()%10;
    sleep(rnd);
    printf("Sono il thread: %ld e ho aspetto %d sec.-> La variabile globale ora è %d \n",pthread_self(),rnd,glob);
    glob++;
    pthread_exit(NULL);
}

int main(int argc, char*argv[]){
if(argc<2){
    printf("inserire il numero di thread da eseguire");
    exit(1);
}
int N= atoi(argv[1]);

pthread_t tid [N];

for(int i=0;i<N;i++){
    pthread_create(&tid[i],NULL,func,NULL);
}

for(int i=0;i<N;i++){
    pthread_join(tid[i],NULL);
}

printf("valore della variabile globale: %d\n", glob);
}
