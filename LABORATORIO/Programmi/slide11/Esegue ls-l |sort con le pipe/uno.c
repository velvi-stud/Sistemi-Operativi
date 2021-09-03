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
int pid; 
int fd[2];
pipe(fd);
if ((pid = fork()) == 0){ /* figlio */
    close(fd[0]);/* chiusura lettura da pipe */ 
    dup2(fd[1], STDOUT);/* redirezione della pipe in scrittura sullo stdout (shell) poichè la sort funziona solo sulla shell*/ 
    execlp("ls", "ls", "-i" , NULL);
    close(fd[1]);
} 
else if (pid > 0){ /* padre */
    close(fd[1]); /* chiusura scrittura su pipe */ 
    dup2(fd[0],STDIN);/* redirezione stdin a pipe */ 
    execlp("sort", "sort", NULL);
    close(fd[1]);
}
}
