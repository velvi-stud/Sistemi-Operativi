#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

#define N 15 /* scrivere numeri da 1 a 15 */

int fdfile; // fd file
sem_t *semprod, *semcons; // semafori

void produce(){
	int cont=0;
	while(cont <= N){
		lseek(fdfile,0,SEEK_SET); // piazzati all'inizio
		sem_wait(semprod);
		write(fdfile,&cont,sizeof(int));
		printf("\n Sono produttore (%d) e scrivo: %d",getpid(),cont);
		sem_post(semcons);
		cont++;
	}
}

void consume(){
	int cont=0;
	while(cont != N){
		if(lseek(fdfile,0,SEEK_SET)==-1); // piazzati all'inizio
		sem_wait(semcons);
		read(fdfile,&cont,sizeof(int));
		printf("\n Sono consumatore (%d) e leggo: %d",getpid(),cont);
		sem_post(semprod);
	}
}

int main(){
	
	fdfile = open("prova.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	
	sem_unlink("/sem1");
	sem_unlink("/sem2");
	
	semprod = sem_open("/sem1", O_CREAT, 0777 ,1);
	semcons = sem_open("/sem2", O_CREAT, 0777 ,0);


	if( write(fdfile,&fdfile,sizeof(fdfile)) != sizeof(fdfile)){
		printf("write error");
		exit(0);
	}

	/* filgio produttore */	
	if(fork()==0){
		produce();
		exit(1);
	}
	/* padre consumatore */
	else{
		consume();
	}

	printf("\nFINE PROGRAMMA\n");
		
	return 0;
}




