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

/*
Nella sala prove del giovane talentuoso chitarrista Matteo Mancuso possono entrare e trovare posto seduto al più
N appassionati chitarristi per una Masterclass con Matteo. I partecipanti rimasti in piedi seguiranno il seminario
successivo. Ogni allievo che ha trovato posto può richiedere ad un collaboratore di Matteo Mancuso un modello di
chitarra degli M modelli messi a disposizione dalla casa produttrice, di cui Matteo Mancuso è testimonial,
considerando che per ogni modello ci sono K chitarre. Quando tutti gli N allievi hanno la propria chitarra, Matteo
suona un pezzo semplice chiedendo a tutti gli allievi di suonarlo insieme a lui. La Masterclass termina quando non
ci sono più chitarristi in attesa.
*/


#define N 5
#define M 2
#define K 3
// M*K = N

#define A  12//students incoming

int a = A;

int xxx = ceil(A/N);

sem_t posti; // N	

pthread_mutex_t m [M];

int guitar [M][K]; // all of 1

pthread_mutex_t chose = PTHREAD_MUTEX_INITIALIZER; //1
int pick = 0;

pthread_mutex_t start= PTHREAD_MUTEX_INITIALIZER; //0
pthread_mutex_t next= PTHREAD_MUTEX_INITIALIZER; //0

pthread_cond_t cond= PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut= PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut2= PTHREAD_MUTEX_INITIALIZER;

void *student(){

	printf("\n Entra %ld \n",pthread_self());

	int I = -1;
	int J = -1;

	sem_wait(&posti);

	pthread_cond_wait(&cond, &mut); // Aspetta l'ok del maestro
	pthread_mutex_unlock(&mut);

	printf("\n %ld trova posto\n",pthread_self());

	for(int i =0; i<M; i++){
	
		pthread_mutex_lock(&m[i]);
		for (int j=0;j<K;j++){
			if (guitar[i][j]==0){
				guitar[i][j]=pthread_self();
				I=i;
				J=j;
				printf("\n %ld, sceglie la chitarra [%d][%d]\n",pthread_self(),I,J);
				break;
			}
		}	
		pthread_mutex_unlock(&m[i]);

		if(I!=-1 && J!=-1){
			pthread_mutex_lock(&chose);
				pick++;
				a--;
				if(pick>=N || a<=0){
					pthread_mutex_unlock(&start);
				}
			pthread_mutex_unlock(&chose);
			break;
		}
	}
	
	//<SUONANO>
	// printf("\n %ld, STA SUONANDO \n",pthread_self());
	pthread_cond_wait(&cond2,&mut2); // aspetta finisca la masterclass
	pthread_mutex_unlock(&mut2);

	pthread_mutex_lock(&chose);
	printf("\n %ld, Esce dall'aula \n",pthread_self());
	pick--; // liberano il posto
	guitar[I][J]=0;
	if(pick<=0){
		pthread_mutex_unlock(&next);
	}
	pthread_mutex_unlock(&chose);
	
	sem_post(&posti);
	printf("\n %ld, CIAO CIAO \n",pthread_self());
	
	return NULL;	
}


void *master(){

	while(xxx-->=0){ //VEDERE
		printf("\n @@@@MASTER %ld, prepara l'aula\n",pthread_self());
		sleep(1);
		pthread_cond_broadcast(&cond); // inizia masterclass nuova
		printf("\n @@@@MASTER %ld, inizio masterclass\n",pthread_self());
		pthread_mutex_lock(&start); // N allievi muniti di chitarra
		 //<SUONANO>
		 printf("\n @@@@MASTER %ld, STA SUONANDO\n",pthread_self());
		 sleep(10);
		 pthread_cond_broadcast(&cond2); // finita masterclass
		 printf("\n @@@@MASTER %ld, dichiara finita la masterclass\n",pthread_self());
		 pthread_mutex_lock(&next);
		 
		 pick = 0; // resetta contatore
		 
	}
	
}

int main(){

	sem_init( &posti, 0, N);

	pthread_mutex_t m [M];
	for (int i = 0; i < M; i++)
	{
		m[i]=(pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
		for (int j = 0; j < K; j++)
		{
			guitar[i][j]=0;
		}
	}

	pthread_mutex_lock(&start);//0
	pthread_mutex_lock(&next); //0

	pthread_t allievi[A], maestro;

	pthread_create(&maestro,NULL,master,NULL);

	for (int i = 0; i < A; i++)
	{
		pthread_create(&allievi[i],NULL,student,NULL);
	}

	for (int i = 0; i < A; i++)
	{
		pthread_join(allievi[i],NULL);
	}

	printf("\nTerminated\n");
	exit(0);
}
