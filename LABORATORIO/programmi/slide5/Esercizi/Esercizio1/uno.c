#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
int main (int argc, char *argv[]){
if (argc < 1){
    printf("\nfornire directory all'avvio");
    exit(353);
}
DIR *cartella = opendir(argv[1]);
if (cartella == NULL){
    perror("\nerrore apertura cartella ");
    exit(542);
}
chdir(argv[1]);
struct dirent *elem;
struct stat info;
while (1){
    elem=readdir(cartella);
    if(elem==NULL){
       return 2;
    }
    printf("\nnome: %s", elem->d_name);
    if(lstat(elem->d_name, &info)<0){ // se ci fosse stato solo la function stat si riferica al file puntato dal link e non al link vero e proprio
        perror("\nstat file error");
        continue;
    }
    if( S_ISLNK(info.st_mode) ){
        printf("\ntrovato link simbolico: %s", elem->d_name);
    }
    else
        printf("  %d\n",info.st_mode);
}
return 4;
}
