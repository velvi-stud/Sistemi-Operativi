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
int main(void){
//uso la vfork
int cpid = vfork();
if(cpid==0){
    printf("\nsono il processo figlio: %d , aspetto 10 sec\n",getpid());
    sleep(5);
    exit(1);
}
else{
    //int stat= waitpid(cpid,&stat,0);
    printf("\nsono il processo padre: %d \n",getpid());
    execl("/bin/ps", "ps", "-elf", NULL);
    exit(0);
}

}
