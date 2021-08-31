// Input output non bufferizzato sullo STDIN STDOUT 
#include<stdio.h>
int main(void){
int c;
while ((c = getc(stdin)) != EOF){
if (putc(c,stdout) == EOF){
printf("errore di output \n");
return(1);
}
if (ferror(stdin)){
printf("errore di input \n");
return(1);
}
}
return(0);
}
//1-35
