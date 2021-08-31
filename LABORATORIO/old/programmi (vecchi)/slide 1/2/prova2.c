//elencare i file di una directory (funziona tipo come comando "ls") in input l'argomento (cartella) argv
#include <sys/types.h>
#include <dirent.h>
#include "apue.h"
int main (int argc, char*argv[])
{
DIR *dp;
struct dirent *dirp;
if(argc != 2)
{
err_quit("a single argument (the dir name) is required");
}
if( (dp = opendir(argv[1])) == NULL)
{
err_sys("can't open %s", argv[1]);
}
while((dirp = readdir(dp)) != NULL)
{
printf("%s\n", dirp->d_name);
}
closedir(dp);
exit(0);
}
//1-23
