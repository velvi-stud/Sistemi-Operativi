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

#define R 4
#define N 20

pthread_t car[N], handler;

pthread_mutex_t mst[4];
int master[4];
pthread_mutex_t ctrl;
pthread_mutex_t verde;
int who; // -1 to 3 | -1 is not setted; 0,1,2,3 are semaphores 
pthread_mutex_t GS;
pthread_mutex_t pass[4];
int go; // -1 to 3 | -1 is not setted; 0,1,2,3 are semaphores 

void W(pthread_mutex_t*x){
	pthread_mutex_lock(x);
}
void S(pthread_mutex_t*x){
	pthread_mutex_unlock(x);
}

void *Auto(void* arg){
	int x = *(int*)arg;
	while(1){
		W(&mst[x]);
		if(master[x]==0){ // Master corsia
			master[x]=1;
			printf("\n ++++ Macchina %ld su corsia %d",pthread_self(),x);
			S(&mst[x]);
			W(&ctrl);
			printf("\n ---- auto %ld (%d) controllo",pthread_self(),x);
			W(&verde);
			who=x;
			S(&verde);
			S(&GS);
		}
		else{
			printf("\n Macchina %ld su corsia %d",pthread_self(),x);
			S(&mst[x]);
		}
		W(&pass[x]);
		if(go==x){
			printf("\n @@@@ Passa l'auto %ld su corsia %d",pthread_self(),x);
			sleep(6);
			S(&pass[x]);
			break;
		}
		else{
			printf("\n #### PECCATO, aspetto");
			S(&pass[x]);
		}
	}
}

void * Gestore(void*args){
	char c;
	while (1){
		printf("\n >>>> wait");
		W(&GS);
		W(&verde);
		go=who;
		printf("\n >>>> corsia verde: %d",who);
		S(&pass[who]);
		sleep(5);
		W(&pass[who]);
		go = -1;
		S(&pass[who]);
		S(&verde);
		S(&ctrl);
		printf("\n >>>> next");
		//scanf("%c",&c);
	}
}

int main(){

	// dichiarazione 
	for (int i = 0; i < R; i++)	{
		mst[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		pass[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	}
	ctrl = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	verde = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	GS = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

	// assegno variabili
	for (int i = 0; i < R; i++)	{
		pthread_mutex_unlock(&mst[i]);
		pthread_mutex_lock(&pass[i]);
		master[i] = 0;
	}
	pthread_mutex_unlock(&ctrl);
	pthread_mutex_unlock(&verde);
	pthread_mutex_lock(&GS);
	who = -1;
	go = -1;

	pthread_create(&handler, NULL, Gestore, NULL);

	int k=0;
	for (int i = 0; i < N; i++)
	{
		k=i%R;
		pthread_create(&car[i], NULL, Auto, &k);
	}

	for (int i = 0; i < N; i++)	{
		pthread_join(car[i],NULL);
	}printf("\n");

	return 0;
}