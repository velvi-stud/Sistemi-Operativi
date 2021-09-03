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

int fd[2];
pipe(fd);
int child1 = fork();
if(child1==0){ // figlio 1 usa la grep <pat> delle cose lette dalla pipe -> aspetta che il padre scriva
    waitpid(getppid(),NULL,0);
    close(fd[WRITE]);
    dup2(fd[READ],READ);
    close(fd[READ]);
    printf("figlio 1\n");
    execlp("grep","grep",argv[1],NULL);
    
    exit(42);
}
else{ //padre usa la ls -R  e scrive sulla pipe
    int ad[2];
    pipe(ad);
    int child2 = fork();
    if(child2==0){ // figlio 2 usa la ls -l e manda direttamente il messaggio al padre
        close(ad[READ]);
        dup2(ad[WRITE],WRITE);
        close(ad[WRITE]);
        printf("figlio 2\n");
        execlp("ls","ls","-l",NULL);
        
        exit(43);
    }
    else{ // padre usa la sort -> aspetta che il figlio 2 scriva sullo STDOUT e manda il risultato la figlio 1
        close(ad[WRITE]);
        close(fd[READ]);
        dup2(ad[READ],READ);
        dup2(fd[WRITE],WRITE);
        close(ad[READ]);
        close(fd[WRITE]);
        printf("padre\n");
        execlp("sort","sort",NULL);
        
        exit(54);
    }
}
return 0;
}
