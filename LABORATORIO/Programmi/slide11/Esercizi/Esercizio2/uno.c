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
#include <signal.h>

/*
scrivere un programma che esegua il comando di shell 
“ls -l| sort| grep <pat>” con tre processi distinti
e scrivere l'output su un file
*/

int main(int argc, char const *argv[])
{
    if(argc<2){
        printf("Inserire pattern\n");
        exit(2);
    }

    int pp[2], oo[2];
    pipe(pp);
    pipe(oo);

    if(!vfork()){

        close(oo[0]); close(oo[1]); close(pp[0]);

        dup2(pp[1],1); // dup scrittura

        close(pp[1]);
        
        execl("/bin/ls","ls","-l",NULL);
        exit(2);
    }

    if(!vfork()){

        close(oo[0]); close(pp[1]);

        dup2(pp[0],0); dup2(oo[1],1); // dup lettura e scrittura

        close(pp[0]); close(oo[1]);
        
        execl("/bin/sort","sort",NULL);
        exit(3);
    }

    if(!vfork()){

        int fds = open("./output_file",  O_CREAT | O_WRONLY |  O_RDONLY | O_TRUNC | O_APPEND, 0777);
        lseek(fds, 1, SEEK_CUR);    /*Si posiziona alla fine del file*/ 

        close(pp[0]); close(pp[1]); close(oo[1]);
        
        dup2(oo[0],0); // dup scrittura
        dup2(fds,1);

        close(oo[0]);
        
        execl("/bin/grep","grep",argv[1],NULL);
        exit(4);
    }

    else{
        exit(5);
    }

    return 0;
}
