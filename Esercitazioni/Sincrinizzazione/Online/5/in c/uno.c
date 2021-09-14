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

#define Max 8
#define N 30

pthread_mutex_t ingresso, uscita;

sem_t enter; // to Max

pthread_mutex_t mut; // =1
int available; // =Max

pthread_mutex_t mut2; // =1
int all; // =Max

pthread_cond_t cond;
pthread_mutex_t mut3;

void *user_s (void *nn){
	
	int num = *(int*)nn;

	// INGRESSO

	printf("\n [%ld] Auto [di %d] entrata \n",pthread_self(),num);

	int v;

    while (1){
		printf("\n#\n");
        pthread_mutex_lock(&mut);
		v= available-num;
		if(available<0 || v < 0){
			printf("\n XXXX non c'è posto per %d auto [%d]\n", num,v);
			printf("\n XXXX actual sit %d\n",available);
			pthread_mutex_unlock(&mut);
		}
		else{
        	available-=num;
			printf("\n ++++ parcheggio di %d posti preso \n",num);
			printf("\n ++++ actual sit %d\n",available);
        	pthread_mutex_unlock(&mut);
			break;
		}
		pthread_cond_wait(&cond,&mut3);
		pthread_mutex_unlock(&mut3);
    }

	printf("\n [%ld] Auto [di %d] parcheggiata \n",pthread_self(),num);

	pthread_mutex_lock(&mut2);
	all++;
	pthread_mutex_unlock(&mut2);

    //-> parcheggio
	//sleep(1);
  

	// USCITA 
	pthread_mutex_lock(&uscita);

	pthread_mutex_lock(&mut);
	printf("\n ---- pargheggio di %d posti lasciato \n",num);
	available+=num;
	printf("\n ---- actual sit %d\n",available);

	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mut);

	pthread_mutex_unlock(&uscita);


	return NULL;
}


int main(){

	printf("\n START MAIN \n");

	ingresso= (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	uscita=(pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	mut = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	mut2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	sem_init(&enter,0,Max);
	
cond=(pthread_cond_t) PTHREAD_COND_INITIALIZER;
mut2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

	available=Max;
	all=0;

	printf("\n END DECLARTION MAIN \n");

	pthread_t autoo[N];

	int k[N];

	srand(time(NULL));
	for (int i = 0; i < N; i++){
		if(i%5==0){ // ogni 5 auto, c' un gruppo di 4
			k[i]=1+rand()%5;
		}else
			k[i]=1;

		pthread_create(&autoo[i],NULL,user_s,&k[i]);
	}

	sleep(2);

    for (int i = 0; i < N; i++)
        pthread_join(autoo[i],(void**)NULL);


    printf("\nTERMINATED %d all:%d\n",available,all);
	exit(2);
	return 0;
}
