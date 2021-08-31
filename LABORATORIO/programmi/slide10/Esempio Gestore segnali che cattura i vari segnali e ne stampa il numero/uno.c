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

static void sig_usr(int signo)// signo è il numero del segnale
{ // un solo handler per tutti
if      (signo == SIGUSR1) printf("received SIGUSR1\n");
else if (signo == SIGUSR2) printf("received SIGUSR2\n");
else if (signo == SIGINT) printf("received SIGINT\n");
else if (signo == SIGTSTP) printf("received SIGTSTP\n");
else printf("received signal %d\n", signo); 
return;
}

int main(void){
printf("Sono il processo: %d\n",getpid());
if (signal(SIGUSR1, sig_usr) == SIG_ERR) 
    printf("can't catch SIGUSR1");
if (signal(SIGUSR2, sig_usr) == SIG_ERR) 
    printf("can't catch SIGUSR2");
if (signal(SIGINT, sig_usr) == SIG_ERR)	// <CTRL C> 
    printf("can't catch SIGINT");
if (signal(SIGTSTP, sig_usr) == SIG_ERR) // <CTRL Z> 
    printf("can't catch SIGTSTP");
while(1) pause();
}

