#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 
int main(int argc, char*argv[]){ 
	
	if (argc!=2){
		printf("inserire path file come argumento... \n"); 
		exit(-1);
	}
	
	if (access(argv[1], R_OK)<0)
		printf("access error for %s\n ", argv[1]);
	else
		printf("read access OK\n");
	
	int flag;
	
	if (flag=open(argv[1], O_RDONLY)<0)
		printf("open error for %s\n", argv[1]);
	else
		printf("open for reading OK\n");
	
	return(0);
}
