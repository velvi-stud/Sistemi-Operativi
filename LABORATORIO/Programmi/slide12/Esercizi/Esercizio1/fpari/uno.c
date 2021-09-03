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
#define size 4

//FIGLIO PARI

int main(){
chdir("../");// mi sposto nella directory superiore ove stanno le fifo

if(access(fifo_pari,F_OK)==-1) //se la fifo del figlio pari non esiste la creiamo
    mkfifo(fifo_pari,0777);
else
    printf("fifo pari esistente\n");
int FIFO_PARI = open(fifo_pari,O_RDONLY);
if(FIFO_PARI == -1){
    perror("Errore apertura fifo pari");
    exit(1);
}

int num;
int sum=0;
while(read(FIFO_PARI,&num,size)>0){
    sum+=num;
    printf("\nho ricevuto il numero: %d stiamo a somma: %d\n", num, sum);
}

close(FIFO_PARI);

FIFO_PARI= open(fifo_pari,O_WRONLY);

write(FIFO_PARI,&sum,size);

close(FIFO_PARI);

unlink(fifo_pari);
}
