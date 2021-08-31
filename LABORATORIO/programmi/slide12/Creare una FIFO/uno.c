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
#include <math.h>
#include <signal.h>

int main(){
int res = mkfifo("./esempio_fifo", 0777); 
if (res == 0)
    printf("FIFO creata\n"); 
else
    printf("FIFO NON creata\n"); 
exit(0);
}
