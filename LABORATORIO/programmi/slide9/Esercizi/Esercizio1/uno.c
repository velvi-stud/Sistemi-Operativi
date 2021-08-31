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
int status;
int cp = vfork();
if(cp == 0){
    printf("processo child 1: \n");
    int i,fibo[12];
    fibo[0]=1;
    fibo[1]=1;
    for (i=1; i<12; i++){
            fibo[i+1]=fibo[i-1]+fibo[i];
    }
    exit(fibo[i]);
}
else{
    waitpid(cp,&status,0);
    if (WIFEXITED(status) && WEXITSTATUS(status) > 50){ //: controlla che lo stato di uscita del figlio sia normale & che il valore di ritorno del figlio sia > 50
        printf("term. normale, exit status =%d\n",WEXITSTATUS(status));
        int cp2 = vfork();
        if (cp2==0){
            printf("processo child 2: \n");
            execl("/bin/ls","ls","-al","exe",NULL);
            exit(3);
        }
        else{
            waitpid(cp2,&status,0);
            printf("Terminazione dei processi, Programma Terminato\n");        
        }
    }
}
return 2;
}

