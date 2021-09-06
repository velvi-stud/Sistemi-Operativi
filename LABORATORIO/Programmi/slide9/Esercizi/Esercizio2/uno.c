#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include "math.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 
#include <sys/wait.h>

#define DEPTH 5

void make(int k, int d);
void stampa(int i, int k);

void main(){
    make(1,0);
}

void stampa(int i, int k){
    printf("%d-> sono: %d il figlio di %d depth:%d\n",i,getpid(),getppid(),k);
    sleep(i);
}

void make(int k, int d){
    if(d==DEPTH){
        exit(3);
    }
    stampa(k,d);
    for (int i = 0; i < 3; i++)
    {
        if(!fork()){
            make(k++,d++);
            exit(4);
        }
    }
    
}
