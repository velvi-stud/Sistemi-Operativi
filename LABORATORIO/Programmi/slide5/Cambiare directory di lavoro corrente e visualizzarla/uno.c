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

int main(int argc, char**argv){

	if(argc<2){
		printf("Inserire cartella su cui spostasi \n");
		exit(1);
	}

	char *cwd=malloc(MAX_PATH);
	
	int size;
	getcwd(cwd,MAX_PATH);
	printf("\n @ Directory corrente: %s", cwd);
	
	/* cambio directory di lavoro */
	if (chdir(argv[1]) < 0)
		perror("chdir fallito");

	if(getcwd(cwd,MAX_PATH) < 0)
		perror("errore get cartella corrente");
		
	printf("\n @ Directory lavoro cambiata: %s\n", cwd);  
	
exit(0);
}
