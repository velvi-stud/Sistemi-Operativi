#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUFFS 4096 
int main(){
int n;
int flag;
char buf[BUFFS];
int fds= STDIN_FILENO;
int fdd=STDOUT_FILENO;
while(1){
n=read(fds, buf, BUFFS);
if(n>0){
    flag = write(fdd, buf, n);
    if(flag!=n){
    printf("write error");
    exit(1);
    }
}
else if (n < 0){
    printf("read error");
    exit(2);
}
}
exit(0);
}




/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#define BUFFS 4096 
int main(void)
{
int n;
char buf[BUFFS];
int fds= STDIN_FILENO;
int fdd=STDOUT_FILENO;
while ((n=read(fds, buf, BUFFS)) > 0) 
if (write(fdd, buf, n) != n)
printf("write error");
if (n < 0)
printf("read error");
exit(0);
}
*/
