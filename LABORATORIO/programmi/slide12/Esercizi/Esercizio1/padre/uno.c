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

#define fifo_pari "./fifo_even"
#define fifo_dispari "./fifo_odd"
#define size 4 //size di un intero

//PADRE

int main(int argc, char *argv[]){

chdir("../");// mi sposto nella directory superiore ove stanno le fifo
printf("aspettanso che si connettano i figli e le rispettive fifo\n");
sleep(5);

int FIFO_PARI = open(fifo_pari,O_WRONLY); // apro figlio pari in scrittura
int FIFO_DISPARI = open(fifo_dispari,O_WRONLY); // apro figlio dispari in scrittura
if(FIFO_DISPARI == -1 || FIFO_PARI == -1){
    perror("Problemi apertura fifo dei figli");
    exit(2);
}
printf("le fifo dei figli sono state aperte correttamente\n");

int num;
int flag;
scanf("%d",&num);
while(num>0){
printf("hai inserito il numero: %d\n",num);
    if(num%2==0){
        flag=write(FIFO_PARI,&num,size);
        if(flag<size){
            perror("errore scrittura fifo pari");
            exit(3);        
        }
    }
    else{
        flag=write(FIFO_DISPARI,&num,size);
        if(flag<size){
            perror("errore scrittura fifo dispari");
            exit(4);        
        }
    }
scanf("%d",&num);
}
close(FIFO_DISPARI);
close(FIFO_PARI);

FIFO_PARI= open(fifo_pari,O_RDONLY);
FIFO_DISPARI= open(fifo_dispari,O_RDONLY);


int sumpar, sumdisp;
read(FIFO_PARI,&sumpar,size);
read(FIFO_DISPARI,&sumdisp,size);

printf("UNA SOMMA DEI PARI E': %d\n",sumpar);

printf("UNA SOMMA DEI DISPARI E': %d\n",sumdisp);

close(FIFO_DISPARI);
close(FIFO_PARI);

exit(10);

}








