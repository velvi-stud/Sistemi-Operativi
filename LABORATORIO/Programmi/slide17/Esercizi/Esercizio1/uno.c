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
#include <limits.h>

int N;
int min=INT_MAX;

struct argument{
    int *arr;
    int index;
};

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;

//passing func((void*)matrix[i]);
void *func(void *par){
    struct argument *arg= (struct argument *) par;
    int somma=0;
    int is_even=1;
    if(arg->index%2==0){
        is_even=1;
        printf("%ld->(%d) è pari\n",pthread_self(),arg->index);
    }else{
        printf("%ld è dispari\n",pthread_self());
    }
    
    if(is_even){
        for(int i=0;i<N;i=i+2){
            somma=somma+arg->arr[i];
        }
    }
    else{
        for(int i=1;i<N;i=i+2){
            somma=somma+arg->arr[i];
        }
    }
    
    pthread_mutex_lock(&mutex);
    if (somma<min){
        min=somma;
    }
    pthread_mutex_unlock(&mutex);
    printf("%ld, somma: %d\n",pthread_self(),somma);
    pthread_exit(NULL);
}


int main(int argc, char**argv){

if(argc<2){
    printf("expected 'N'");
    exit(0);
}
N = atoi(argv[1]);

int **matrix = (int **)malloc(N * sizeof(int*));
for(int i = 0; i < N; i++) matrix[i] = (int *)malloc(N * sizeof(int));

for(int i= 0 ; i < N ; i++){
    matrix[i]=(int*)malloc(N*sizeof(int));
    for(int j = 0 ; j < N ; j++){
            matrix[i][j]= (rand()%256);
    } 
}


for(int i= 0 ; i < N ; i++){
    for(int j = 0 ; j < N ; j++){
            printf("%d\t",matrix[i][j]);
    } printf("\n");
} printf("\n\n");

pthread_mutex_init(&mutex,NULL);


pthread_t pidt[N];
struct argument arg[N];
for(int i=0;i<N;i++){
    arg[i].arr=(int*)matrix[i];
    arg[i].index=i;
    pthread_create(&pidt[i],NULL,func,&arg[i]);
}

for(int i=0;i<N;i++){
    pthread_join(pidt[i],NULL);
}

printf("il minimo è %d\n",min);

return 2;


}
