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

int N;
char pat;
int flag=0;

struct argument{
    char *arr;
    int row;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//passing func((void*)matrix[i]);
void *func(void *par){
    struct argument *arg= (struct argument *) par;
    for(int i=0;i<N && flag==0;i++){
          if(arg->arr[i]==pat){
                pthread_mutex_lock(&mutex);
                   if (flag==1){
                    pthread_mutex_unlock(&mutex);
                    pthread_exit(NULL);
                    }
                printf(" find result at position. Row: %d Column: %d \n",arg->row+1,i);
                flag=1;
                pthread_mutex_unlock(&mutex);
                pthread_exit(NULL);
          }else{
              printf(" %c ",arg->arr[i]);
          }
    } printf("\n");

    pthread_exit(NULL);
}


int main(int argc, char**argv){
if(argc<3){
    printf("expected 'N' and a char ");
    exit(0);
}
N = atoi(argv[1]);
pat= (char)*argv[2];

char matrix [N][N];
for(int i= 0 ; i < N ; i++){
    for(int j = 0 ; j < N ; j++){
            matrix[i][j]= (char)(65 + rand() %26);
    } 
}

for(int i= 0 ; i < N ; i++){
    for(int j = 0 ; j < N ; j++){
            printf(" %c ",matrix[i][j]);
    } printf("\n");
} printf("\n\n");

pthread_mutex_init(&mutex,NULL);

pthread_t pidt[N];
struct argument arg;
for(int i=0;i<N;i++){
    arg.arr=matrix[i];
    arg.row=i;
    pthread_create(&pidt[i],NULL,func,&arg);
}

for(int i=0;i<N;i++){
    pthread_join(pidt[i],NULL);
}

return 2;


}
