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

char *env_init[]={"USER=sconosciuto", "PATH=/tmp", NULL}; 

int main(void){
pid_t pid;
if ((pid = fork())<0){ 
    perror("Errore fork"); 
    exit(-1);
} 
else if (pid == 0) {
    if (execle("/home/aulainfo/Scrivania/SISTEMI OPERATIVI/LABORATORIO/programmi (nuovi)/slide6-7/Esempio processi con execvv/due", "esempio uno con execle", "exec -> LE", "altro arg a caso", NULL, env_init) <0){
        perror("Errore execle"); 
        exit(-1);
    }
}
if (waitpid(pid,NULL,0) <0){ 
    perror("Errore wait"); 
    exit(-1);
}
if ((pid = fork()) <0) { 
    perror("Errore fork"); 
    exit(-1);
} 
else if (pid == 0) {
    if (execlp("/home/aulainfo/Scrivania/SISTEMI OPERATIVI/LABORATORIO/programmi (nuovi)/slide6-7/Esempio processi con execvv/due","esempio due con exexlp","con exec -> LP", NULL)<0){ 
        perror("errore execlp");
        exit(-1);
    }
}
exit(0);
}
