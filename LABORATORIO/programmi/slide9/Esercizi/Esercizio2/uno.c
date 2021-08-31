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
int lc(int i){return 3*i+1;}
int cc(int i){return 3*i+2;}
int rc(int i){return 3*i+3;}

int main(){
int a = 3; // n foglie
int h = 4; // altezza albero
int i,j;
//albero ternario perfetto strutturato tramite array
int nodes = (pow(a,h)-1)/2;
int chpid[nodes*3];
printf("\n------> sono in totale %d nodi\n",nodes);
for(i=0;i<nodes;i++){
    chpid[i]=vfork();
    if(chpid[i]==0){
            printf("%d-> sono: %d il figlio di %d\n",i,getpid(),getppid());
            chpid[lc(i)]=fork();
            if(chpid[lc(i)]==0){printf("figlio sx di %d\n",getppid()); exit(1);}
            chpid[cc(i)]=fork();
            if(chpid[cc(i)]==0){printf("figlio ce di %d\n",getppid()); exit(2);}
            chpid[rc(i)]=fork();
            if(chpid[rc(i)]==0){printf("figlio dc %d\n",getppid()); exit(3);}
            sleep(1);
            exit(0);
    }
}
return 20;
}
