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

char *frase = "Messaggio..."; 

int main() {
int fd[2], bytesRead;
char message[100];
pipe(fd); 
if(fork() == 0) { /*figlio*/
    close(fd[READ]); 
    write(fd[WRITE],frase,strlen(frase)+1); 
    close(fd[WRITE]);
}
else { /*padre*/
    close(fd[WRITE]);
    bytesRead=read(fd[READ],message,100);
    printf("Letti %d byte: %s\n", bytesRead, message);
    close(fd[READ]);
}
}
