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
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5 

unsigned long int buf[N], last;
int x, z, j;

pthread_mutex_t m =  PTHREAD_MUTEX_INITIALIZER; //1
pthread_mutex_t s = PTHREAD_MUTEX_INITIALIZER;  //0 
pthread_mutex_t ok = PTHREAD_MUTEX_INITIALIZER; //0 
pthread_mutex_t b =  PTHREAD_MUTEX_INITIALIZER; //0 
pthread_mutex_t v =  PTHREAD_MUTEX_INITIALIZER; //1
pthread_mutex_t me = PTHREAD_MUTEX_INITIALIZER; //0;



void *thfun(){
    printf("\n ++++ %lu Entro processo figlio \n",pthread_self());
    while(1){
		pthread_mutex_lock(&ok);
        printf("\n ++++ %lu Entro in ok \n",pthread_self());
		pthread_mutex_lock(&m);
		if(z<N && buf[x]==-1){ // se ci sono numeri da estrarre e se la posizione estratta è da assegnare
			printf("\n ++++ %lu ottenuto numero %d \n",pthread_self(),z);
            buf[x] = pthread_self();
			z++;
			last = pthread_self();
			pthread_mutex_unlock(&s); // sblocco il coordinatore 
			pthread_mutex_unlock(&m);
			break;
		}
		else if(z >= N){ // estratti tutti i numeri
            printf("\n ++++ %lu estrazione finita \n",pthread_self());
			pthread_mutex_unlock(&m);
			return NULL; // esco
		}
		else{ // se il buffer era già assegnato, reitero per cercare di aggiudicare un altra posizione 
			printf("\n ++++ %lu non ce l'ha fatta, reitera \n",pthread_self());
            pthread_mutex_unlock(&m);
		}	
	}
	
	pthread_mutex_lock(&v);
	if (last != pthread_self()){ // non sono l'ultimo processo
		pthread_mutex_unlock(&v);
		return NULL;
	}

	// sono l'ultimo processo
	printf("**** %lu *****",last);

    pthread_mutex_unlock(&me);

	while(j != N){
		pthread_mutex_lock(&v);
		printf("\n $$$$ %lu buf[%d]=%lu\n",pthread_self(),j,buf[j]);
		j++;
		pthread_mutex_unlock(&me);
	}
    
}





void *coor(){

    while (1){
        printf("\n @@P@@ %lu estraggo numero \n",pthread_self());
		pthread_mutex_lock(&m);
		x++; // shoud be random
        if(z>=N){
            break;
        }
		pthread_mutex_unlock(&m);
		pthread_mutex_unlock(&ok); // sblocco i child per l'aggiudico della posizione x
        pthread_mutex_lock(&s); // aspetta che uno di loro abbia scelto e che mi sblocchi per la prossima pesca
    }

    printf("\n @@P@@ %lu fine estrazione \n",pthread_self());
	
	while(j != N){
		pthread_mutex_lock(&me);
		printf("\n §§§§ %lu buf[%d]=%lu\n",pthread_self(),j,buf[j]);
		j++;
		pthread_mutex_unlock(&v);
	}

}

int main(int argc, char const *argv[])
{
    /* inizializzazione */
    for (int i = 0; i < N; i++) buf[i]=-1;
    pthread_mutex_lock(&s);
    pthread_mutex_lock(&ok);
    pthread_mutex_lock(&b);
    pthread_mutex_lock(&me);

    x = -1; // shoud be random
    z = 0;
    last = -1;
    j = 0;

    /* launching */

    pthread_t coordinator;
    pthread_t child [N];

    pthread_create(&coordinator,NULL,coor,NULL);
    for (int i = 0; i < 2*N; i++){
        pthread_create(&child[i],NULL,thfun,NULL);
    }
    
    pthread_join(coordinator,NULL);

    printf("\nTerminated\n");
    exit(4);
    return 0;
}
