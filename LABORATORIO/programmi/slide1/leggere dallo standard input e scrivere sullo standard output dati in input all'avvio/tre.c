#include <stdio.h> 
#include <stdlib.h>
int main(void){
int c;
while ((c = getc(stdin)) != EOF) 
if (putc(c,stdout) == EOF){
printf("errore di output\n"); 
exit(1);
}
if (ferror(stdin)){
printf("errore di input\n"); 
exit(1);
}
exit(0);
}
