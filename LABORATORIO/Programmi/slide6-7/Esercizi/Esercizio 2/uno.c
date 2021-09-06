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
#include <fcntl.h>
#include <unistd.h>

// ulteriore implementazione della pipe per vedere:
// con ps axo stat,pid,pid,comm
// poi grep -w defunct

void stampa(char*c){
    printf("\n %s(%d) figlio di: %d",c,getpid(),getppid());
}

int main(int argc, char const *argv[]){
    
    int pp[2];
    pipe(pp);

    int child[2];
    child[0]=vfork();
    if(child[0]!=0){
        child[1]=vfork();
    }
    
    if(!child[0]){ // child process
        stampa("child");
        close(pp[0]);
        dup2(pp[1],1);
        execl("/bin/ps","ps","-s",NULL);
        exit(3);
    }
    else if(!child[1]){ // child process 2
        wait((int*)NULL);
        stampa("child");
        close(pp[1]);
        dup2(pp[0],0);
        execl("/bin/grep","grep","Z+",NULL); //check zombie process
        exit(4);
    }
    else{ // father
        stampa("father");
        sleep(120); // to make zombie process his child
        while(wait((int*)NULL)){
            printf("\n Aspetto");
        }
    }

    printf("\n Terminato");

    return 0;
}
