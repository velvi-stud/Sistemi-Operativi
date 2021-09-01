#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>

void funexit(void){
    printf("\n (funzione) USCITA %d\n", getpid());
    return;
}


int main (int argc, char *argv[]) { 

    if (argc != 2){ /* controllo argomenti */ 
        fprintf(stderr, "Uso: %s processi\n", argv[0]); 
        return 1;
    }

    /* setta funzione di uscita */
    atexit(funexit);

    printf("\nSTART: %d",getpid());
    int i, n;
    pid_t childpid;
    pid_t waitreturn;
    pid_t flag;
    n = atoi(argv[1]);

    for (i = 1; i <= n; i++){      
        if ( (childpid=fork) == 0){
            printf("\n ...Blocco istruzioni processo: %d (figlio di %d)", getpid(), getppid());
            break;
        }else{
            printf("\n%d: eseguo fork, esito: %d",i, childpid);
        }
    }

    /* usciranno i processi creati (ed il padre) */

    if(argc != 0) {
        while((childpid != (waitreturn = wait(NULL)))){
        printf("\nsono: %d aspetto: %d", getpid(), waitreturn);
            if (waitreturn == -1)
                break;
        }
    }

    exit(0);
}
