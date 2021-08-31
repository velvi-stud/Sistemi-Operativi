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
#include <stdio.h>
int main (int argc, char *argv[]) { 
if (fork () == 0) { /* Figlio */
execvp (argv[1], &argv[1]); /* Esegue un altro programma */ 
fprintf (stderr, "Non ho potuto eseguire %s\n", argv[1]);
}
}
