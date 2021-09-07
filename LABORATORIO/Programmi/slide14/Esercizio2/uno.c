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
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 

#define N 6

// VARIABILI GLOBALI
int mid = N/2 ; // N diviso 2
int i; // id process
int pid[N]; // pid process
char command; // command a, b
int fd[2]; // file descriptor pipe

static void handler(int signo){ //sighandler 
if (signo == SIGUSR1) printf("%d -> received %c SIGUSR1\n",i,command);
}


int body_proc(int id){
    printf("sono il processo: %d, con id=%d\n",getpid(),i);
    if ( command == 'a' ){
        if(i%2 == 0){ //pari
            read(fd[0],pid,sizeof(pid));
            kill(pid[i+1],SIGUSR1);
        }
        else{ //dispari
            pause();
        }
    }
    else if ( command == 'b' ){
        if(i<mid){
            read(fd[0],pid,sizeof(pid));
            kill(pid[i+mid],SIGUSR1);
        }
        else{
            pause();        
        }
    }
return 0;
}



int main (int argc, char *argv[]){

if(argc<2){
    printf("inserire variabile comando");
    exit(0);
}
command = (char)*argv[1];

signal(SIGUSR1,handler);
//creazione di una pipe
pipe(fd);
int flag;

for(i=0;i<N;i++){
    pid[i]=fork();
    if(pid[i]==0){
        close(fd[1]); //chiudo descrittore che non mi serve -> faccio solo read
        body_proc(i);
        close(fd[0]); // una volta finito la read
        exit(0);
    }
}

// Padre
close(fd[0]); // chiudo il descrittore file inutilizzato -> faccio solo write
for (i=0; i<N;i++){
    write(fd[1],pid,sizeof(pid));
}
close(fd[1]); //chiudo una volta finito
exit(0);

}
