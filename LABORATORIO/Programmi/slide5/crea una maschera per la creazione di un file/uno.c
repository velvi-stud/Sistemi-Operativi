#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 

int main(void) {

	umask(0);
	creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // annulla i permessi che ci sono come argomento
	creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // sarà solo S_IRUSR | S_IWUSR 
	
	exit(0);
}
