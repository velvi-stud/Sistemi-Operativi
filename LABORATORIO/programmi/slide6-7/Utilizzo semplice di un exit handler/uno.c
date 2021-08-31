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

static void my_exit1(void){ printf("Primo exit handler\n");}

static void my_exit2(void){ printf("Secondo exit handler\n");}

int main (void){
if (atexit(my_exit2)!=0)
    printf("Non posso registrare my_exit2");

if (atexit(my_exit1)!=0)
    printf("Non posso registrare my_exit1"); 

if (atexit(my_exit1)!=0)
    printf("Non posso registrare my_exit1"); 

printf("Main ha completato\n");
return(0);
}


