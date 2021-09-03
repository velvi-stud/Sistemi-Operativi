#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <math.h>
#include <signal.h>

int p0, p1;

void when_term(){
    kill(p0,SIGINT);
    printf("\n processo figlio 1 terminato \n");
}

void stampapid(){
    printf("\n Pid-> %d \n",getpid());
}

int main( int argc, char **argv){
	int N, N1, N2;
    char *C;
    if (argc!=5){
        printf("\n Inserire bene gli argomenti \n");
        exit(1);
    }
    N=atoi(argv[1]);
    N1=atoi(argv[2]);
    N2=atoi(argv[3]);
    C = argv[4];

    if((p0 = fork())==0){ // son 1
        sleep(N1);
        execlp(C,C,NULL);
        perror("EXEX");
        exit(2);
    }
    else if((p1=fork())==0){ // son 2
        signal(SIGALRM,when_term);
        alarm(N2);
        for(int i=0;i<N;i++){
            sleep(1);
            kill(getppid(),SIGUSR1);
        }
        printf("\n processo figlio 2 terminato \n");
    } 
    else{ // papa
        signal(SIGUSR1,stampapid);
        for(int i=0;i<N;i++){
            pause();
        }
        waitpid(p0,NULL,0);
        waitpid(p1,NULL,0);
        printf("\n processi figli terminati \n");
    }


}