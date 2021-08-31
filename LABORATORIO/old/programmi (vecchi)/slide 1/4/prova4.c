//controllo processi (_definire processo_)
#include <sys/types.h>
#include <sys/wait.h>
#include "apue.h"
int main(void){
char buf[MAXLINE];
pid_t pid;
int status;
printf("%% "); /* print prompt (printf requires %% to print %) */
while (fgets(buf, MAXLINE, stdin) != NULL) 
{
buf[strlen(buf) - 1] = 0; /* replace newline with null */
if ( (pid = fork()) < 0)
{
err_sys("fork error");
}
else if (pid == 0) 
{ /* child */
execlp(buf, buf, (char *) 0);
err_ret("couldn't execute: %s", buf);
exit(127);
}
if ( (pid = waitpid(pid, &status, 0)) < 0)
{
err_sys("waitpid error");
}
printf("%% ");
} 
exit(0);
}
//1-40
