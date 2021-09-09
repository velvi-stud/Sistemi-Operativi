#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
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
#include <semaphore.h>

#define N 5
#define R 100

pthread_t cliente[R], barbiere;

sem_t barber; // 0
pthread_mutex_t aspetto; // 1
int sedie; // incluse quella per il taglio
pthread_mutex_t taglio; // 1
unsigned long tid;

void W(pthread_mutex_t*x){
	pthread_mutex_lock(x);
}
void S(pthread_mutex_t*x){
	pthread_mutex_unlock(x);
}

void *_Barbiere(void* arg){
	while(1){
		printf("\n Barbiere aspetta");
		sem_wait(&barber);
		S(&taglio);
			// taglia capelli
		printf("\n @@@@ Barbiere taglia capelli");
	}
}

void *_Cliente(void*args){
	sleep(rand()%3);
	W(&aspetto);
	if(sedie<N){ 
		printf("\n ---- Cliente %ld entra e si siede al posto %d\n", pthread_self(), sedie);
		sedie++;
		S(&aspetto);
	}
	else{
		printf("\n $$$$ Cliente %ld entra e NON si siede \n", pthread_self());
		S(&aspetto);
		exit(2);
	}

	sem_post(&barber);
	W(&taglio);
	// taglio capelli
	printf("\n ++++ Cliente %ld taglia capelli",pthread_self());

	//lascio posto
	W(&aspetto);
	printf("\n ^^^^ Cliente %ld lascia il posto",pthread_self());
	sedie --;
	S(&aspetto);
	
	printf("\n §§§§ Cliente %ld TERMINA",pthread_self());

	return NULL;
}

int main(){

	sem_init(&barber, 0, 0);	
	aspetto = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	taglio = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;


	pthread_mutex_unlock(&aspetto);
	pthread_mutex_lock(&taglio);
	sedie = 0;

	srand(time(NULL));

	pthread_create(&barbiere, NULL, _Barbiere, (void*)NULL);

	for (int i = 0; i < R; i++){
		pthread_create(&cliente[i], NULL, _Cliente, (void*)NULL);
	}

	for (int i = 0; i < R; i++)	{
		pthread_join(cliente[i],NULL);
	}printf("\n");

	return 0;
}
