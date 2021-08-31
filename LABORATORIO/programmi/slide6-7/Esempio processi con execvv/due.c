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

int main(int argc, char * argv[]){ 
printf("\nEseguo programma\n");
int	i;
char **ptr; 

for (i=0; i < argc; i++) // echo di tutti gli arg da riga di cmd 
printf("argv[%d]: %s\n", i, argv[i]);

extern char **environ;
for (ptr = environ; *ptr !=0; ptr++) /* echo stringhe di env */ 
printf("%s\n", *ptr);
exit(0);
}
