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

void stamp(char *c){
	printf("\n%s-> processo: %d padre: %d \n",c,getpid(),getppid());
} 

#define PathExe "/bin/ls"

int main (void) {

	stamp("start");
	pid_t childpid= vfork();
	stamp("after fork");	
	if(childpid == 0){
		stamp("inside son");
		execl(PathExe, "ls", "-l", NULL); /* Esegue ls -l */ 
		printf("Questa riga non dovrebbe essere eseguita\n");
		exit(22);
	}
	
	waitpid(childpid,NULL,0); // aspetto figlio termini
	printf("programma terminato\n");

}
