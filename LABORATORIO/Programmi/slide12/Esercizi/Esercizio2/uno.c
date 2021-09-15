#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>          
#include <sys/stat.h>
 
/*
Processo prod. e cons.
Il processo prod. genera un numero casuale da 1 a MAX per N volte e invio un intero per volta al processo cons.
Il Processo cons. una volta ricevuti N interi fa la somma di questi interi e invia la somma al processo produttore.
*/

#define MAX 10
#define N 5

void fcons(){
	int fp = open("./toprod",O_WRONLY);
	int fc = open("./tocons",O_RDONLY);
	int number;
	for (int i = 0; i < N; i++){
		number=1+rand()%MAX;
		write(fp,&number,sizeof(int));
	}
	read(fc,&number,sizeof(int));
	printf("\n# la somma è di: %d\n",number);
}

void fprod(){
	int fp = open("./toprod",O_RDONLY);
	int fc = open("./tocons",O_WRONLY);
	int number=-1, sum=0;
	for (int i = 0; i < N; i++){
		read(fp,&number,sizeof(int));
		printf("@ numero generato: %d\n",number);
		sum+=number;
	}
	write(fc,&sum,sizeof(int));
}

int main(){

	if(unlink("./toprod")<0 || unlink("./tocons")<0 )
		printf("\n Fifo già presenti, cancellazione...");
	
	printf("Creazione fifo...\n");
	mkfifo("./toprod", 0777);
	mkfifo("./tocons", 0777);
	

	if(!fork()){ // figlio
		fprod();
		exit (1);
	}
	else{ // padre
		fcons();
		exit (3);
	}

}
