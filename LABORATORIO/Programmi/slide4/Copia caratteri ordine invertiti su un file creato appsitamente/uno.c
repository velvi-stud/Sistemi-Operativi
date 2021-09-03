#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
int main(int argc, char *argv[]) { 
int fds, fdd;
int flag, ctr=0;
char buff;
if (argc == 0) {
    printf("specificare gli argomenti in input\n"); 
    exit(1);
}

fds = open(argv[1], O_RDONLY);
lseek(fds, 1, SEEK_END);    /*Si posiziona alla fine del file*/ 

fdd = open("reverse.txt", O_CREAT | O_WRONLY, 0600);
lseek(fdd,0,SEEK_SET); /*Si posiziona all'inizio del file*/

while (1) /*legge il file al contrario: ad ogni passo sposta il puntatore di due passi indietro, perché la lettura lo aggiorna */
{
    flag = lseek(fds, -2*sizeof(char), SEEK_CUR);  // si posiziona  -2*sizeof(char) poichè legge un char e si posiziona al byte prima del char letto
    if(flag != -1){
        read(fds, &buff, sizeof(char));
        write(fdd, &buff, sizeof(char));
    }
    else{
        return 1;
    }
    printf("%c",buff);
}
return 0;
}
