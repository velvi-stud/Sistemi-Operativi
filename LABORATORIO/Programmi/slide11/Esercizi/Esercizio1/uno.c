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

int main(int argc, char *argv[]){
if(argc<2){
    printf("Inserire un pattern\n");
    exit(-2);
}else{
    if(strlen(argv[1])>=50){
        printf("size pattern eccessivo\n");   
        exit(-3); 
    }
}

int buffer;
int fd[2];
pipe(fd);
int child =fork();
if(child==0){ // figlio usa la grep <pat> delle cose lette dalla pipe -> aspetta che il padre scriva
    close(fd[WRITE]);
    dup2(fd[READ],READ);
    execlp("grep","grep",argv[1],NULL);
    close(fd[READ]);
}
else{ //padre usa la ls -R  e scrive sulla pipe
    close(fd[READ]);
    dup2(fd[WRITE],WRITE);
    execlp("ls","ls","-R",NULL);
    close(fd[WRITE]);
}
return 0;
}
