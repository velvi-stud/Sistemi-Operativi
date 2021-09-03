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
int glob=6; /* variabile esterna (blocco dati inizializzati) */   
int main(void)
{
int var; /* variabile automatica sullo stack */  
pid_t pid;
var = 88;
printf("prima della fork\n");
if ((pid = vfork())<0) { 
    printf("errore della vfork");
 } 
else if (pid ==0){ /*figlio*/
    glob++; /*modifico la varibile*/
    var++;
    _exit(0); /*finisce processo figlio*/
}
/* il padre continua qui */
printf("pid = %d, glob = %d (6), var = %d (88)\n",getpid(),glob,var); exit(0);
}
