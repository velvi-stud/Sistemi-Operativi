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
Scrivere un programma che gestisce il comportamento di un padre e due figli (fpari e fdispari); 
il padre legge numeri positivi da tastiera fino a che non arriva un numero negativo: 
    se il numero è pari lo manda al figlio pari, 
    altrimenti lo manda al figlio dispari.
I figli effettuano le somme parziali, quindi 
    rimandano le somme al padre 
    che calcola la somma totale e la stampa a video
TUTTO USANDO LA FIFO
*/

void _fpari(){
	int fifoeven = open("./fifopari",O_RDONLY);
	int fifotot = open("./fifotot",O_WRONLY);
	int s, somma = 0;
	while(read(fifoeven, &s, sizeof(int))>0){
		somma +=s;
	}
	close(fifoeven);
	write(fifotot, &somma, sizeof(int));
	close(fifotot);
	printf("\nsomma figlio pari = %d",somma);
}

void _fdispari(){
	int fifoodd = open("./fifodispari",O_RDONLY);
	int fifotot = open("./fifotot",O_WRONLY);
	int s, somma = 0;
	while(read(fifoodd, &s, sizeof(int))>0){
		somma +=s;
	}
	close(fifoodd);
	write(fifotot, &somma, sizeof(int));
	close(fifotot);
	printf("\nsomma figlio dispari = %d", somma);
}

void _padre(){
	int fifoeven = open("./fifopari",O_WRONLY);
	int fifoodd = open("./fifodispari",O_WRONLY);
	int fifotot = open("./fifotot",O_RDONLY);
	int s, somma=0;

	while(1){
		fflush(stdin);
		printf("\n Inserire un numero: ");
		scanf("%d",&s);
		if(s<0){
			break;
		}
		if(s%2==0){
			write(fifoeven, &s, sizeof(int));
		}else{
			write(fifoodd, &s, sizeof(int));
		}
	}
	close(fifoeven);
	close(fifoodd);
	
	while (read(fifotot, &s, sizeof(int))>0)
	somma += s;

	printf("\n somma padre = %d", somma);

	close(fifotot);
}

int main(){

	if(unlink("./fifopari")<0 || unlink("./fifodispari")<0 || unlink("./fifotot")<0)
		printf("\n Fifo già presenti, cancellazione...");

	printf("\n Creazione fifo...");

	mkfifo("./fifopari", 0777);
	mkfifo("./fifodispari", 0777);
	mkfifo("./fifotot", 0777);

	if(!fork()){ // figlio pari
		_fpari();
		exit (1);
	}
	else if(!fork()){ // figio dispari
		_fdispari();
		exit (2);
	}
	else{ // padre
		_padre();
		exit (3);
	}

}
