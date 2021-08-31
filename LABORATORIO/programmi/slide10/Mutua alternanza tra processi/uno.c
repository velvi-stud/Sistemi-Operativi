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
#include <signal.h> 
#include <stdio.h> 

void siges1(int signo){
printf("sono nel gestore segnali del processo 1\n");
    if(signo == SIGSTOP)
        signal(signo, SIG_DFL);
    else if(signo == SIGCONT)
        signal(signo, SIG_DFL);
    else if(signo == SIGINT){
        signal(signo, SIG_DFL);
        exit(11);
    }
    else 
        printf("error signal %d\n",signo);
return;
}

void siges2(int signo){
printf("sono nel gestore segnali del processo 2\n");
    if(signo == SIGSTOP)
        signal(signo, SIG_DFL);
    else if(signo == SIGCONT)
        signal(signo, SIG_DFL);
    else 
        printf("error signal %d\n",signo);
return;
}

int main (void) { 
int pid1;
int pid2;

pid1 = fork ();
if (pid1 == 0) { /* Primo figlio */ 
    signal(SIGSTOP, siges1);
    signal(SIGCONT, siges1);
    signal(SIGINT, siges1);
    while (1) {/* Ciclo infinito */
        printf ("pid1 is alive\n"); 
        sleep (1);
    }
}

pid2 = fork ();
if (pid2 == 0) { /* Secondo figlio */ 
        signal(SIGSTOP, siges2);
        signal(SIGCONT, siges2);
        signal(SIGINT, SIG_DFL);
    while (1) { /* Ciclo infinito */
        printf ("pid2 is alive\n"); 
        sleep (1);
    }
}

sleep (2);
kill (pid1, SIGSTOP); /* Sospende il primo figlio */ 

sleep (2);
kill (pid1, SIGCONT); /* Ripristina il primo figlio */ 

sleep(2);
kill (pid2, SIGINT); /* termina il secondo figlio */ 

sleep (2);
kill (pid1, SIGINT); /* termina il primo figlio */ 



return 0;
}
