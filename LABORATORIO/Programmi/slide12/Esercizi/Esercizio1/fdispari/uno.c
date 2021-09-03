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
#define fifo_dispari "./fifo_odd"
#define size 4

//FIGLIO DISPARI

int main(){
chdir("../"); // mi sposto nella directory superiore ove stanno le fifo

if(access(fifo_dispari,F_OK)==-1) //se la fifo del figlio dispari non esiste la creiamo
    mkfifo(fifo_dispari,0777);
else
    printf("fifo esistente\n");
int FIFO_DISPARI = open(fifo_dispari,O_RDONLY);
if(FIFO_DISPARI == -1){
    perror("Errore apertura fifo dispari");
    exit(1);
}

int num;
int sum=0;
while(read(FIFO_DISPARI,&num,size)>0){
    sum+=num;
    printf("\nho ricevuto il numero: %d stiamo a somma: %d\n", num, sum);
}

close(FIFO_DISPARI);

FIFO_DISPARI= open(fifo_dispari,O_WRONLY);

write(FIFO_DISPARI,&sum,size);

close(FIFO_DISPARI);

unlink(fifo_dispari);
}
