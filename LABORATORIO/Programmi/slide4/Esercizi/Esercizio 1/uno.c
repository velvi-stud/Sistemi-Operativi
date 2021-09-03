#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
int main(){
int flag=1;
char op1;
char op2;
char space;
int o1,o2,o3;
printf("start \n");
while(1){
//prima la fase di read
read(0,&op1,1);
read(0,&space,1);
read(0,&op2,1);
fflush(0);
if(op1 == '-' && space == '1') exit(2);
o1= (op1)-48; o2= (op2)-48; o3=o1+o2;
    printf("\nprimo numero: %c", op1);   
    printf("\nsecondo numero: %c", op2);     
    printf("\nrusultato: %d \n",o3);  
read(0,&space,1); //non so ma mi saltavala prima read all'inizio dovevo inserirlo
}
return 0;
}
