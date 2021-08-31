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

int main ()
{
int fds[2]; 
pid_t pid;
pipe (fds);/* Crea una pipe. I descrittori per le estremità sono in fds.*/  
if ((pid = fork()) == 0) { /* Crea un processo figlio. */ 
    close (fds[WRITE]); /* Processo figlio. Chiude descrittore lato scrittura */ 
    dup2 (fds[READ], STDIN_FILENO); /* Connette il lato lettura della pipe allo standard input. */ 
    execlp ("sort", "sort", NULL); /* Sostituisce il processo figlio con il programma “sort”. */ 
}
else { /* Processo genitore */
    close (fds[READ]);/* Chiude il descrittore lato lettura */ 
    write(fds[WRITE], "This is a test.\n", 16); 
    write(fds[WRITE], "My dog has fleas.\n",18 ); 
    write(fds[WRITE], "Hello, world.\n", 14); 
    write(fds[WRITE], "This program is great.\n",23); 
    write(fds[WRITE], "One fish, two fish.\n",20);
    close (fds[WRITE]);
    waitpid (pid, NULL, 0);/* Aspetta che il processo figlio finisca */ 
}
return 0;
}
