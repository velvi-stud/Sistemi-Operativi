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
#include <math.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <pthread.h>

/*
Leggere i file della directory corrente, 
    se il file letto è un directory mostrare il contenuto 
    della directory 
    (Non mostrare i contenuti di eventuali sotto-directory)   
    e creare un processo figlio che mostra lo stesso contenuto però utilizzando il comando ls.
Buon proseguimento.
*/

void executepid(char*c){
    chdir(c);
    printf("\n #### PROCESS: %s\n",c);
    execlp("/bin/ls","ls","-l",NULL);
}

int main(int argc, char const *argv[])
{   

    char tt[1024];
    getcwd(tt,1024);
    DIR* direc = opendir(tt);
    if(direc==NULL){
        puts("Errore aperture dir");
        exit(3);
    }

    struct dirent* fileinto, *filenasted;
    DIR *othdir;

    pid_t pid;
    
    while(fileinto=readdir(direc)){

        if(fileinto->d_type==DT_DIR){

            if(fileinto->d_name[0]=='.')
                continue;

            printf("\n\n\n @@@@ MAIN: %s\n",fileinto->d_name);

            othdir=opendir(fileinto->d_name);

            printf("Contenuto directory: \n");

            while(filenasted=readdir(othdir)){
                if(filenasted->d_name[0]=='.')
                continue;
                printf("%s\n",filenasted->d_name);
            }            

            if(!(pid=fork())){
                executepid(fileinto->d_name);
                exit(2);
            }else{
                waitpid(pid,NULL,0);
            }
            
        }
    }

    return 0;
}
