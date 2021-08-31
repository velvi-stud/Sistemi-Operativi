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
#define READ 0
#define WRITE 1
#define size 4096

int main(int argc, char*argv[]){
if(argc<2){
printf("Richiesti argomenti\n");
exit(1);
}
printf("inserito: %s\n",argv[1]);
int fd[2];
int temp;
pipe(fd);
char message[size];
pid_t child=fork();
if(child==0){ //figlio legge
    close(fd[WRITE]);
    temp=read(fd[READ],message,size);
    close(fd[READ]);
    printf("letti: %d byte \nLETTI: %s\n",temp,message);
}
else{  //padre scrive
    close(fd[READ]);
    temp=write(fd[WRITE],argv[1],strlen(argv[1])+1);
    close(fd[WRITE]);
    printf("scritti: %d byte\nSCRITTI: %s\n",temp,argv[1]);
}
}
