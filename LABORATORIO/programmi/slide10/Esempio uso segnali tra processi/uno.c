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
#include <math.h>
#include <signal.h>
#include<stdio.h>
#include<sys/types.h> 
#include<sys/wait.h> 
#include<signal.h> 
#include<stdlib.h>

static void handler(int signo) /* operazione alla ricezione di una kill */
{
if (signo == SIGUSR1)
    printf("\n (padre) RICEVUTO INTERRUPT SIGUSR1\n"); 
else     
    printf("\n (padre) RICEVUTO SEGNALE NON IDENTIFICATO \n"); 
return;
}

int main(void){
int i;
int chpid = fork();
if ( chpid == 0){	/* processo figlio */
    printf("\n(figlio) il mio process-id e`%d\n",getpid());
    printf("\n(figlio) aspetto 3 secondi e invio un segnale a: %d\n",getppid());
    for (i=0; i<3; i++){
        sleep(1); 
        printf("+\n");
    }
    kill(getppid(),SIGUSR1); 
printf("\n(figlio) ho finito e muoio\n");
exit(0);
}
else{	/* processo padre */
    signal(SIGUSR1,handler); /* se dovessero inviare questo messaggio allora se lo vedrà il gestore handler (creato appositamente)*/
    printf("\n(padre) il mio process-id %d\n",getpid()); 
    printf("\n(padre) incomincio le mie operazioni -> aspetto 6 secondi\n"); 
    for (i = 0; i < 6; i++){
        sleep(1);
        printf("-\n");
    }
    printf("\n(padre) ora muoio anch'io\n"); 
    exit(0);
}
return 0;
}

