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

#define N 2
#define M 4
#define T 2 //sec

sem_t posti[N]; // all of M
pthread_mutex_t mut[N]; // all of 1
int occuped[N]; //all of 0

pthread_mutex_t drive[N], startime[N]; // all of 0

pthread_cond_t cond[N]; 
pthread_mutex_t ok[N];

pthread_cond_t cond2[N]; 
pthread_mutex_t ok2[N];

pthread_mutex_t varmut[N]; // all of 1
int vartemp[N]; // all of 0;

int full[N];

void *autobus(void *v){
    int num = *(int*) v;

	//printf("\n @@@@ %d ATTIVO\n",num);

    while(full[num]>0){
        printf("\n @@@@ %d ASPETTA \n",num);

      
	    pthread_mutex_lock(&startime[num]); // il primo ad entrare fa partire l'allame
		printf("\n @@@@ %d PRIMO PASSEGGERO ENTRATO \n",num);
        
        pthread_mutex_lock(&drive[num]); // l'ultimo sblocca la partenza se l'alarm non suona
			//printf("\n @@@@ %d ULTIMO PASSEGGERO ENTRATO \n",num);
        
		printf("\n @@@@ %d SI PARTE \n",num);
        
        pthread_cond_broadcast(&cond[num]); // avviso i passeggeri che stiamo per partire
        pthread_mutex_lock(&mut[num]); // così nessun altro passeggero vede i posto
        
		// -> DRIVE

		sleep(2);

		printf("\n @@@@ %d ARRIVATI \n",num);
        
        pthread_cond_broadcast(&cond2[num]); // dico ai passeggeri che siamo arrivati

        occuped[num] = 0; // resetto variabile dei posti
        pthread_mutex_unlock(&mut[num]); // sblocco la verifica dei nuovi passeggeri
    }
}


void *utente(void *v){

    int num = *(int*) v;

//    printf("\n %ld WAIT BUS [%d]\n",pthread_self(),num);

    sem_wait(&posti[num]);

    pthread_mutex_lock(&mut[num]);
		full[num]--;
		occuped[num]++;
        if (occuped[num]==1){ // first sit
		printf("\n [%d] %ld frst sit on %d",num,pthread_self(),occuped[num]);
            pthread_mutex_unlock(&startime[num]); 
        }
        else if(occuped[num]>=M){ // last sit or last passegners
		printf("\n [%d] %ld last sit on %d",num,pthread_self(),occuped[num]);
            pthread_mutex_unlock(&drive[num]);
        }
		else if(full[num]<=0){
			pthread_mutex_unlock(&drive[num]);
		}
		else{
			printf("\n [%d] %ld take sit on %d",num,pthread_self(),occuped[num]);
		}
    pthread_mutex_unlock(&mut[num]);

    // aspetto che l'autista parta 
    pthread_cond_wait(&cond[num],&ok[num]);
    pthread_mutex_unlock(&ok[num]);

//	printf("\n %ld GOOOO!!! [%d]\n",pthread_self(),num);

    // aspetto che l'autista sia arrivato alla fine
    pthread_cond_wait(&cond2[num],&ok2[num]);
    pthread_mutex_unlock(&ok2[num]);

//    printf("\n %ld ARRIVATI [%d]\n",pthread_self(),num);

    sem_post(&posti[num]);
	return (void*)NULL;
}


int main(){

	printf("\n START MAIN \n");

	for (int i = 0; i < N; i++)
	{
		sem_init( &posti[i], 0, M);
		mut[i]= (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		occuped[i]=0;
		drive[i]= (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER; 
		pthread_mutex_lock(&drive[i]);
		startime[i]= (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_lock(&startime[i]);
		cond[i]=(pthread_cond_t) PTHREAD_COND_INITIALIZER;
		ok[i]= (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		cond2[i]=(pthread_cond_t) PTHREAD_COND_INITIALIZER;
		ok2[i]= (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		varmut[i]= (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		vartemp[i]=0;
		full[i]=0;
	}

	printf("\n END DECLARTION MAIN \n");

	int nu = M*N;

	pthread_t bus[N], user[nu];

	int k[nu], l[N];

	for (int i = 0; i < nu; i++){ // calcolo quanti passeggeri per autobus
		k[i]=i%N;
		full[i%N]++;
	}
	for (int i = 0; i < N; i++) 
		printf("\n %d person for bus %d \n",full[i],i);
	

	/* creo gli autisti */
    for (int i=0; i<N; i++){
		l[i]=i;
        pthread_create(&bus[i],NULL,autobus,&l[i]);
	}

	/* creo e aspetto gli utenti */
    for (int i = 0; i < nu; i++)
        pthread_create(&user[i],NULL,utente,&k[i]);
    for (int i = 0; i < nu; i++)
        pthread_join(user[i],NULL);


    printf("\nTERMINATED\n");
	exit(2);
	return 0;
}