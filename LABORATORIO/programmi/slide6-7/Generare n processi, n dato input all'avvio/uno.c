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
void set(){printf("Processo corrente: %d -> Generato da: %d\n",getpid(),getppid());}
int main(int argc, char *argv[]){
if(argc == 1){
    printf("Dare un numero in input\n");
    exit(1);
}
int i;
pid_t childpid;
printf("START %d\n",getpid());
for(i=0;i<atoi(argv[1]);i++){
printf("%d-> %d\n",i,getpid());
    childpid= fork();
    if(!childpid){
        printf("%d-> ",i);
       set();    
    }
    else{
        printf("%d-> %d\n",i,getpid());   
    }
}
printf("%d-> fine processo %d\n",i,getpid());  
exit(0);
}
