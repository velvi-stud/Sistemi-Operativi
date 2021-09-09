#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define C 20
#define N 5

int credito[N];
int P[N];
int cont_processi_ok = 0;
int processi_in_gioco= N;
int max_indice;
int tmp = 0;
unsigned long tid[N];
unsigned long tidMax;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *esecuzione(void *arg);

int main(int argc, char const *argv[])
{
	
	int i;
	pthread_t processi[N];

	srand(time(NULL));

	printf("\tCREDITO DI TUTTI\n ");
	for(i=0;i<N;i++)
		printf("%d\t",i);

	printf("\n ");

	for(i=0;i<N;i++){
		credito[i]=C;
		printf("%d \t",credito[i]);

	}
	printf("\n\n");

	for(i=0;i<N;i++){
		pthread_create(&processi[i],NULL,esecuzione,(void * )&i);
		sleep(1);
	}

	for(i=0;i<N;i++){
		pthread_join(processi[i],NULL);
	}

	return 0;
}

void *esecuzione(void *arg){

	int *indice = (int *)arg;
	int i = *indice;
	int j,max;

	tid[i] = pthread_self();
	sleep(N-i);
	
	while(1){
	
		//P[i] = 1+rand()%C; // scelgo il numero random
		P[i]=credito[i]/2;
		
		pthread_mutex_lock(&mutex); // entro nella sezione critica

		if(processi_in_gioco == 1){ // se sto giocando da solo, vuol dire che ho vinto
			printf("**HO VINTO  %d %lu**\n",i,pthread_self());
			return NULL;
		}

		cont_processi_ok++; // ho scelto e sono in gioco
		printf("VALORE ESTRATTO DA %d: %d\n",i,P[i]);
		
		if(processi_in_gioco > cont_processi_ok){ // se ci sono ancora processi in gioco che devono scegliere
		/* Sezione fatta da tutti eccetto uno*/
			pthread_cond_wait(&cond,&mutex); // aspetto @@@@
			pthread_mutex_unlock(&mutex); //esco dalla sezione critica
		}
		
		else if(processi_in_gioco == cont_processi_ok){  // se tutti i processi in gioco hanno scelto CONTROLLO
		/*---> Questa sezione la farà solo uno degli N processi */
			max = P[i]; // massimo valore è il mio (default)
			max_indice = i;	// ovviamente anche l'indice 
			tidMax = pthread_self(); // e il process id
			tmp = 0;
			for(j=0;j<N;j++){ // controlla tutto l'array per trovare il vincitore
				if(P[j]<=0)
					continue;
				if(max<P[j] || (max == P[j] && tidMax>tid[j])){
					max = P[j];
					max_indice = j;
					tidMax = tid[j];
				}
				else{
					tmp += P[j];
				}
			}
			
			cont_processi_ok = 0; // setta tutti i processi non disponibili
			
			pthread_mutex_unlock(&mutex); // sblocca la sezione critica
			
			pthread_cond_broadcast(&cond); // sblocca tutti i processi che sono in attesa dell'assegnazione
		}

		/* Sezione fatta da tutti */
		if(max_indice == i){ // se sono il processo che ha l'indice che corrisponde al processo vincente
			credito[i] += tmp; // accredito
			printf("SONO **%d** e sono il MAX, credito[%d] = %d TID %lu\n",i,i,credito[i],pthread_self());
		}
		
		else{ // se non sono il processo vincitore
			credito[i] -= P[i];	 // decremento il numero generato dal credito
			if(credito[i] <= 0 || P[i]==0){ // se il credito è minore di 0, sono fuori dal gioco
				printf("SONO %d e NON sono il MAX, credito[%d] = %d TID %lu HO PERSO xxxx\n",i,i,credito[i],pthread_self());
				P[i] = -1; // segno che deve saltare il controllo quando si estrae il massimo
				pthread_mutex_lock(&mutex2);	// sezione critica variabile
				processi_in_gioco--;	// elimino i processi in gioco
				pthread_mutex_unlock(&mutex2);	// esco sezione critica
				return NULL;
			}
			else{ // se il credito è > 0, sono ancora in gioco 
				printf("SONO %d e NON sono il MAX, credito[%d] = %d TID %lu #### %d\n",i,i,credito[i],pthread_self(),P[i]);
			}
		}
		sleep(1);
	}
}
