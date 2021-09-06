#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main (){

	if (!fork()) { // child
		printf("\n child process %d",getpid());
		exit (0);
	}
	else { // father
		printf("\n father process %d",getpid());
		sleep (120);
	}
	return 0;
}
