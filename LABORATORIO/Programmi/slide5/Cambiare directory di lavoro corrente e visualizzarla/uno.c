#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h"
#define MAX_PATH 4096
int main(void)
{
char *cwd=malloc(MAX_PATH);
int size;
/* cambio directory di lavoro */
if (chdir("/home/aulainfo/Scrivania/cartella_prova") < 0)
perror("chdir fallito");

if(getcwd(cwd,MAX_PATH) < 0)
perror("errore get cartella corrente");
printf("cwd = %s\n", cwd);  
exit(0);
}
