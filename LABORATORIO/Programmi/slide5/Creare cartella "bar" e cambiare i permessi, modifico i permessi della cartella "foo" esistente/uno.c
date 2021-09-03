#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "apue.h" 
#define PATH_MAX 4096
int main(void)
{

char *currentfolder=malloc(PATH_MAX);
if(getcwd(currentfolder,PATH_MAX)==NULL)
perror("errore cartella");
//printf("%s\n",currentfolder);

/* creo una carella nella directory presente aggiungendo "/bar" */
umask(0);
strcat(currentfolder,"/");
char *namenewfolder="bar";
if(mkdir(strcat(currentfolder,namenewfolder),0600)<0)
printf("mkdir error for %s\n",namenewfolder);
printf("NEW PATH: %s\n",currentfolder);

/* modo assoluto a "rw-r--r--" */
if (chmod(namenewfolder, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
perror("chmod error for bar");
printf("chmod ok for %s, new permits: rw-r--r--\n",namenewfolder);

/* apre lo stat di foo per gli st_mode */ 
struct stat statbuf;
if (stat("foo", &statbuf) < 0) // ricerca foo nella cartella di lavoro se non specifichi il path
perror("stat error for foo");
else
printf("stat ok for foo\n");

/* impostai suoi vecchi permessi ed inserisce il set-group-ID e disattiva group-execute */ 
if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
perror("chmod error for foo");
else
printf("chmod ok for foo, new permits %d\n",statbuf.st_mode);

exit(0);
}
