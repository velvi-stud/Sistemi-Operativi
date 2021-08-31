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
int main (){
int pid;
printf ("Sono il processo di partenza con PID %d e PPID %d.\n",getpid(),getppid()); 
pid = fork (); /* Duplicazione. Figlio e genitore continuano da qui */
if (pid != 0) { /* pid diverso da 0, sono il padre */
printf ("Sono il processo padre con PID %d e PPID %d.\n",getpid(),getppid()); 
printf ("Il PID di mio figlio e %d.\n", pid); /* non aspetta con wait(); */
}
else { /* il pid è 0, quindi sono il figlio */
printf ("Sono il processo figlio con PID %d e PPID %d.\n",getpid(),getppid());
}

printf ("PID %d termina.\n",getpid());
/* Entrambi i processi eseguono questa parte */ 
return 0;
}
