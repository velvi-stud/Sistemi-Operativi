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

#define N 10 // < 10 make child || don't
#define X 60

void stampa(char*c){
    printf("\n %s(%d) figlio di: %d",c,getpid(),getppid());
}

int fibo(int n){
    int n1=0,n2=1, n3;
    for (int i = 2; i <= n; ++i)
    {
        n3=n2+n1;
        n1=n2;
        n2=n3;
    }
    return n3;
}

int main(int argc, char const *argv[]){
    
    int pid=fork();
    if(!pid){ //child
        exit(fibo(N));
    }
    else{ //father
        int status;
        waitpid(pid,&status,0);
        if (WIFEXITED(status)) {
            int exitstatus= WEXITSTATUS(status);
            printf("Figlio 1 terminato, status=%d\n", exitstatus );
            if (exitstatus<X){
                int pid2=fork();
                if(!pid2){
                    execl("/bin/ls","ls","-al",NULL);
                    exit(22);
                }
                else{
                    waitpid(pid2,(int*)NULL,0);
                    printf("figlio 2 terminato\n");
                }
            }
        } else if (WIFSIGNALED(status)) {
            printf("killed by signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("stopped by signal %d\n", WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("continued\n");
        }
               exit(EXIT_SUCCESS);

    }

    

    printf("\n Terminato");

    return 0;
}

