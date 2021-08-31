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

void funexit(void){
    printf("\nUSCITA %d\n", getpid());
    return;
}

void status(){printf("\n processo %d, padre %d",getpid(),getppid());}
void status2(){printf("\nCREAZIONE sta il processo %d, padre %d",getpid(),getppid());}
void start(int i){printf("\n%d-> START p: %d",i,getpid());}
void end(int i){printf("\n%d-> FINE p: %d",i,getpid());}

int main (int argc, char *argv[]) { 
if (argc != 2){ /* controllo argomenti */ 
    fprintf(stderr, "Uso: %s processi\n", argv[0]); 
    return 1;
}

atexit(funexit);
start(0);
int i, n;
pid_t childpid;
pid_t waitreturn;
pid_t flag;
n = atoi(argv[1]);

for (i = 1; i <= n; i++){
    childpid = fork();
    start(i);
    if (childpid == 0){
        printf("\nBlocco istruzioni processo: %d", getpid());
        break;
    }
}

if(argc != 0)
printf("\nsono: %d aspetto: %d", getpid(), waitreturn);
while((childpid != (waitreturn = wait(NULL)))){
printf("\nsono: %d aspetto: %d", getpid(), waitreturn);
    if (waitreturn == -1)
        break;
}
end(i);
exit(0);
}
