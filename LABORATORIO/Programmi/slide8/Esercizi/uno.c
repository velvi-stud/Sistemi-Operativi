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
int main(){
printf("in attesa\n");
int cpid = vfork();
if(cpid == 0){
    execl("/bin/ls","ls","-l",NULL);
    exit(0);
}
else{
    int stat = waitpid(cpid,&stat,0);
    printf("creazione nuovo figlio\n");
    int cpid2 = fork();
    if(cpid2 == 0){
        sleep(5);
        printf("hai aspettato 5 secondi\n");  
        exit(1);  
    }
    else{
        stat = waitpid(cpid2,&stat,0);
        printf("ora il processo %d ha finito\n",cpid2);
    }
}
}
