#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 
int main(int argc, char *argv[])
{
int i;
struct stat buf;  
char *ptr;
for (i = 1; i < argc; i++) { 
    printf("%s: ", argv[i]);

    if (lstat(argv[i], &buf) < 0)
        printf("lstat error\n");

    else if (S_ISREG(buf.st_mode)) 
        ptr = "regular";
    
    else if (S_ISBLK(buf.st_mode))	
        ptr = "block special";

    else	
        ptr = "** unknown mode **"; 

    printf("%s\n", ptr);
}
exit(0);
}
