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
#define STDIN 0
#define STDOUT 1

int main(){
int fd[2];
pipe(fd);
int son;
if((son=fork())==0){ //figlio scrive
    close(fd[STDIN]);
    dup2(fd[STDOUT],STDOUT);
    execlp("ls","ls","-l",NULL);
    close(fd[STDOUT]);
}
else{
    close(fd[STDOUT]);
    dup2(fd[STDIN],STDIN);
    execlp("wc","wc","-w",NULL);
    close(fd[STDIN]);
}
}
