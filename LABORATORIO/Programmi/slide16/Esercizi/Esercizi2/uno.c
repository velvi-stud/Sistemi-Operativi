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

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ops= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;

int counter=0;
int limit;

void *func_12 (void *arg){
int num;

    for(int i=0;i<500;i++){
        num = 1+rand()%10;

        pthread_mutex_lock(&mutex); // blocca il mutex
        
        if(pthread_mutex_trylock(&ops)==0){
            pthread_mutex_unlock(&ops);
        }else{
            pthread_mutex_unlock(&ops); 
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

         if(counter>=limit){
            pthread_cond_signal(&cond);
            pthread_mutex_lock(&ops);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        counter=counter+num;
        printf("%ld counter: %d\n",pthread_self(),counter);

        pthread_mutex_unlock(&mutex);
    }
 pthread_exit(NULL);
}


void *func_3 (void *arg){ 
    alarm(5);
    pthread_cond_wait(&cond,&mutex);
    printf("il contatore ha raggiunto %d è >= %d\n",counter,limit);
    pthread_exit(NULL);
}



int main(int argc, char**argv){
if(argc<2){
    printf("too poor value, expectid a number");
    exit(0);    
}
limit=atoi(argv[1]);

pthread_mutex_init(&mutex,NULL);
pthread_mutex_init(&ops,NULL);

pthread_t pidt[3];

pthread_create(&pidt[0],NULL,func_12,NULL);
pthread_create(&pidt[1],NULL,func_12,NULL);
pthread_create(&pidt[2],NULL,func_3,NULL);

pthread_join(pidt[0],NULL);
printf("thread 1 finito\n");
pthread_join(pidt[1],NULL);
printf("thread 2 finito\n");
pthread_join(pidt[2],NULL);
printf("thread 3 finito\n");
    exit(2);
}
