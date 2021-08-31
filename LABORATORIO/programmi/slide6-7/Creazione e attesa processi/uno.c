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

int main (int argc, char *argv[]) { 
if (argc != 2){ /* controllo argomenti */ 
    fprintf(stderr, "Uso: %s processi\n", argv[0]); 
    return 1;
}

atexit(funexit);
printf("\nSTART: %d",getpid());
int i, n;
pid_t childpid;
pid_t waitreturn;
pid_t flag;
n = atoi(argv[1]);

for (i = 1; i <= n; i++){
status2();
    printf("\n%d: prima dalla fork",i);
    childpid = fork();
    printf("\n%d: eseguo fork, esito: %d",i, childpid);
    if (childpid == 0){
        printf("\nBlocco istruzioni processo: %d", getpid());
        break;
    }
}

//printf("\n sono %d e aspetto: %d",getpid(), waitreturn);
status();
if(argc != 0)
while((childpid != (waitreturn = wait(NULL)))){
printf("\nsono: %d aspetto: %d", getpid(), waitreturn);
    if (waitreturn == -1)
        break;
}

exit(0);
}
