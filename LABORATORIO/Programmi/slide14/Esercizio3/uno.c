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

int N;
int N1;
int N2;
char* command;
int p1, p2;

void timeout(int signo){
printf("processo %d, finito\n",getpid());
kill(SIGINT,p1);
}

void gestoreP(int signo){
printf("padre %d, ricevuto messaggio\n",getpid());
return;
}

int main(int argc, char*argv[]){
if(argc<5){
printf("inserire gli argomenti");
exit(1);
}
N=atoi(argv[1]);
N1=atoi(argv[2]);
N2=atoi(argv[3]);
command=malloc(sizeof(argv[4])); strcpy(command,argv[4]);

p1=fork();
if(!p1){ //child 1
    sleep(N1);
    execlp(command,command,NULL);
    pause();
    exit(2);
}

p2 = fork();
if(!p2){ // child 2
    signal(SIGALRM,timeout);
    alarm(N2);
    // for sinc with father
    for(int i=1;i<N;i++){
        sleep(1);
        kill(getppid(),SIGUSR1);
    }
exit(4);
}

//for sinc with child2
signal (SIGUSR1,gestoreP);
for(int i=1;i<N;i++){
    pause();    
}

int status,pf,stat;
//aspetta la wait generica da 2 figli
for(int i=0;i<2;i++){
    pf=wait(&status);
    if(stat=WIFEXITED(status)){
        printf("term. ok: %d. Con stato %d\n",pf,stat);    
    }
    else{
        printf("term: %d Non corretta, seganle %d\n", pf,stat);    
    }
}

return 0;
}
