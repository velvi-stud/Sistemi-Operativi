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
#include <stdio.h> 
#define READ 0
#define WRITE 1
int main (int argc, char *argv []) { 
int fd [2];
pipe (fd); 
/* Crea una pipe senza nome */ 
if (fork () != 0) { /* Padre, scrittore */
    close (fd[READ]); /* Chiude l’estremità non usata */
    dup2 (fd[WRITE], 1); /* Duplica l’estremità usata allo stdout */ 
    close (fd[WRITE]); /* Chiude l’estremità originale usata */
    execlp (argv[1], argv[1], NULL); /* Esegue il programma scrittore */ 
    perror ("connect"); /* Non dovrebbe essere eseguita */
}
else { /* Figlio, lettore */
    close (fd[WRITE]); /* Chiude l’estremità non usata */
    dup2 (fd[READ], 0); /* Duplica l’estremità usata allo stdin */ 
    close (fd[READ]); /* Chiude l’estremità originale usata */
    execlp (argv[2], argv[2], NULL); /* Esegue il programma lettore */ 
    perror ("connect"); /* Non dovrebbe essere eseguita */
}
}
