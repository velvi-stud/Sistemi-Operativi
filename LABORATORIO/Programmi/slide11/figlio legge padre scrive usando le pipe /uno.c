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
#define SIZE 1024

int main(int argc, char*argv[]) { 
int pfd[2];
int nread; int pid;
char buf[SIZE];

if (pipe(pfd)== -1) {
    perror("pipe() fallita)"); 
    exit(-1);
}
if((pid=fork()) < 0 ) {
    perror("fork() fallita"); 
    exit(-2);
}

if(pid==0) { /* figlio */ 
    close(pfd[1]);
    read(pfd[0], buf, SIZE);
    printf("il figlio legge: %s\n", buf);
    close(pfd[0]);
}
else { /* padre */ 
    close(pfd[0]); 
    strcpy(buf,"Sono tuo padre!");
    write(pfd[1], buf, strlen(buf)+1); 
    close(pfd[1]);
}
exit(0);
}
