#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	char nameDirectory[4096];
	char nomefilelinkato[4096];
	int max=-1, n;
	char linkMax[1024];

	struct  dirent *elem;
	struct stat info,infol;

	getcwd(nameDirectory,sizeof(nameDirectory));

	DIR *cartella = opendir(nameDirectory);
	if (cartella == NULL){
    	perror("\n errore apertura cartella ");
    	exit(542);
	}

	while(elem = readdir(cartella)){
	
		if(elem==NULL){
			continue;
		}

		lstat(elem->d_name,&infol);

		if(S_ISLNK(infol.st_mode)){
		
			printf("link simbolico %s ",elem->d_name);
			
			n = readlink(elem->d_name,nomefilelinkato,4096);
			nomefilelinkato[n]='\0';
			
			printf("riferimento a %s ",nomefilelinkato);
			
			//repersico il file puntato dal link tramite stat
			stat(elem->d_name,&info);		
			
			printf("con dimensione di %ld\n",info.st_size);
			
			if(info.st_size>max){
				max= info.st_size;
				strcpy(linkMax,elem->d_name);
			}
			
		}
	}

	printf("\nNOME FILE %s con dimensione %d\n",linkMax,max);


	return 0;
}
