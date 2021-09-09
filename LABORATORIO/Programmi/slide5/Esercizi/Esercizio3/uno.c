#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char const *argv[])
 {
 	if(argc!=2){
 		printf("Usage: Inserire path cartella\n");
 		exit(-1);
 	}

 	
 	struct dirent *elementi;
 	struct stat info;
 	int namelen;
 	char buf[1024];

 	DIR *dir = opendir(argv[1]);
 	
 	if((dir  == NULL)){
 		perror("openddir");
 		exit(-2);
 	}

 	while((elementi =readdir(dir)) != NULL){

 		if(lstat(elementi->d_name,&info)<0){
 			perror("lstat");
 			exit(-3);
 		}

 		printf("\nFILE: %s",elementi->d_name);
 		if(S_ISLNK(info.st_mode)){

 			printf("E' UN LINK SIMBOLICO, CHE PUNTA AL FILE: ");

 			if(stat(elementi->d_name,&info)<0){
 				perror("stat");
 				exit(-4);
 			}

 			if((namelen = readlink(elementi->d_name,buf,1024))<0){
 				perror("readlink");
 				exit(-5);
 			}
 			buf[namelen] = '\0';

 			printf("%s di SIZE %d\n", buf,(int)info.st_size);
 		}

 	}



 	return 0;
 } 
