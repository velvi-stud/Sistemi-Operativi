#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
int main (int arcg, char *argv[]){
struct stat buf;
char *surce="doc1.txt";
char *dest="doc2.txt";
int fds = open(surce,O_RDONLY);
if (fds == -1){
    printf("errore apertura fd: %d \n",fds);
    return 1;
}
int fst = fstat(fds, &buf);
if (fst<0){
    printf("errore controllo fd: %d \n",fst);
    return 2;
}
off_t buffsize = buf.st_blksize;
printf("best buffersize: %ld di: %d \n",buffsize,fds);
char buff[buffsize];
int fdd = open(dest,O_WRONLY);
int n;
int flag;
while(1){
    n= read(fds,buff,buffsize);
    if(n>0){
        flag = write(fdd,buff,n);
        if(flag != n){
            printf("errore scrittura");
            return 1;
        }
    }
    else{
        printf("errore lettura");
        return 2;    
    }
}
return 0;
}

