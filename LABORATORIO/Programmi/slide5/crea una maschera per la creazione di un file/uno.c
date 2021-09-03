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
if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
printf("creat error for foo");

umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // annulla i permessi che ci sono come argomento
if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0) // sarà solo S_IRUSR | S_IWUSR 
printf("creat error for bar"); 
exit(0);
}
