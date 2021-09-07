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

/*
Scrivere un programma in C e Posix sotto Linux che, 
preso un argomento intero positivo da riga di
comando, gestisca la seguente situazione:
	 genera due figli A e B e
	 - se l'argomento è PARI 
        invia un segnale SIGUSR1 alla ricezione 
        del quale il figlio A calcola il cubo del
	    numero passato come argomento da linea di 
        comando, mentre il figlio B stampa un 
        messaggio di arrivederci e termina.
	 - se l'argomento è DISPARI
        invia un segnale SIGUSR2 alla ricezione 
        del quale il figlio B calcola il
	    reciproco del numero passato come argomento, 
        attende per un numero di secondi pari al doppio 
        del numero passato come argomento ed invia un 
        segnale SIGUSR1 al processo A dopodiché termina
	    l'esecuzione. Il figlio A, invece, attende la 
        ricezione del segnale SIGUSR1, 
        stampa un messaggio e termina.
*/

int out1=0;
float out2=0.0f;
int val;

void ha1(int sn){
    out1 = val*val*val;
    printf("\n A: Cubo del valore %d: %d\n",val,out1);
}

void hb1(int sn){
    printf("\n B: Arrivederci\n");
}

void ha2(int sn){
    printf("\n A: Arrivederci\n");
}

void hb2(int sn){
    out2= pow(val,-1);
    printf("\n B: reciproco del valore %d: %f\n",val,out2);
}

int main(int argc, char const *argv[])
{
    if(argc<2){
        printf("\nInserire correttamente gli argomenti\n");
        exit(2);
    }
    
    val = atoi(argv[1]);
    
    int fa=-1, fb=-1;
    
    if(val%2==0){
        
        if(!(fa=fork())){
            signal(SIGUSR1,ha1);
            pause();
            exit(1);
        }
        else if (!(fb=fork())){
            signal(SIGUSR2,hb1);
            pause();
            exit(2);
        }
        else{
            printf("\n MAIN %d\n", getpid());
            sleep(1);
            kill(fa,SIGUSR1);
            kill(fb, SIGUSR2);

            int wpid, status;
            while ((wpid = wait(&status)) > 0);
            printf("\n Terminati \n");

            exit(3);
        }

    }
    else{

         if(!(fa=fork())){
            signal(SIGUSR1,ha2);
            pause();
            exit(1);
        }
        else if (!(fb=fork())){
            signal(SIGUSR2,hb2);
            pause();
            sleep(val*2);
            kill(fa,SIGUSR1);
            exit(2);
        }
        else{
            printf("\n MAIN %d\n", getpid());
            sleep(1);
            kill(fb,SIGUSR2);

            int wpid, status;
            while ((wpid = wait(&status)) > 0);
            printf("\n Terminati \n");

            exit(3);

        }

    }



    return 0;
}
