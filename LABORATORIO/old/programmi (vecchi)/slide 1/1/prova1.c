//legge in STDIN e stampa in STDOUT (FILENO ossia puoi dare l'i/o anche da file)
#include "apue.h"
#define BUFFSIZE 8192
int main(void)
{
int n;
char buf[BUFFSIZE];
while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
{
if(write(STDOUT_FILENO,buf,n)!=n)
{
err_sys("write error");
}
if(n<0)
{
err_sys("read error");
}
}
exit(0);
}
//1-32
