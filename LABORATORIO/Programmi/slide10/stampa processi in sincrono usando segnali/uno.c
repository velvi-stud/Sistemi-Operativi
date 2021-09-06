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
Lo scopo del programma è creare 2 processi figli che 
vengano eseguiti e stampino un messaggio in un ciclo infinito
*/

#define N 10

int pid1,pid2;
int var=0;

// int flag = 0;
// void handler_0(int signum){
//     if (signum == SIGIO){
//         if (flag!=2){
//             flag++;
//         }
//         else{
//             //printf("\n @@@@ 1:%d 2:%d",pid1,pid2);
//             kill(pid1,SIGUSR1);
//             kill(pid2,SIGUSR2);
//         }
//     }
//     else if (signum == SIGALRM)
//     {
//         exit(20);
//     }
    
// }

void handler_1(int signum){
    if (signum == SIGUSR1){
        printf(" \nPID1: %d",var++);
    }
    else if (signum == SIGALRM)
    {
        exit(20);
    }
    
}

void handler_2(int signum){
    if (signum == SIGUSR2){
        printf("\nPID2: %d",var++);
    }
    else if (signum == SIGALRM)
    {
        exit(30);
    }
}


int main(int argc, char const *argv[]){
//signal(SIGIO,handler_0);
//signal(SIGALRM,handler_0);

    if(!(pid1=fork())){

        signal(SIGUSR1,handler_1);
        signal(SIGALRM,handler_1);
        signal(SIGIO,SIG_IGN);

//        kill(getppid(),SIGIO);
//        pause(); // aspetto di essere attivato
        
        alarm(15); // aspetta 10 sec e finisce
        
        while(1){
            pause();
        }
        
        exit(3);
    }

    else if(!(pid2=fork())){
        
        signal(SIGUSR2,handler_2);
        signal(SIGALRM,handler_2);
        signal(SIGIO,SIG_IGN);

//       kill(getppid(),SIGIO);
//        pause(); // aspetto di essere attivato
        
        alarm(15); // aspetta 10 sec e finisce
        while(1){
            pause();
        }

        exit(4);
    }

    else{
        //*** MAIN ***//
        printf("SHOT %d",getpid());

        while(var++<=N){
            sleep(1);
            kill(pid1,SIGUSR1);
            kill(pid2,SIGUSR2);
        }

        int wpid, status;
        while ((wpid = wait(&status)) > 0);
        printf("\n Terminati \n");

    }

    return 0;
}
