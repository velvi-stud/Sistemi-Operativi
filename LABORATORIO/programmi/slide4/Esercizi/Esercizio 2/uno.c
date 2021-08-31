#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
int main(){
int fds = open("testfile.txt",O_RDONLY);
int fdd = open("outputfile.txt", O_CREAT | O_WRONLY, 0600);
int flag=0;
char op1;
char op2;
char space;
char *op3;
int o1,o2,o3;
printf("start \n");
while(read(fds,&op1,1)>0){
//prima la fase di read
read(fds,&space,1);
read(fds,&op2,1);
fflush(0);
if(op1 == '-' && space == '1') exit(2);
o1= (op1)-48; o2= (op2)-48; o3=o1+o2;
    printf("\nprimo numero: %c", op1);   
    printf("\nsecondo numero: %c", op2);     
    printf("\nrusultato: %d \n",o3);  
read(fds,&space,1); //non so ma mi saltava uno dovevo inserirlo
sprintf(op3,"risultato= %d \n",o3);
write(fdd,op3,sizeof(op3)*2);
flag++;
}
return 0;
}
