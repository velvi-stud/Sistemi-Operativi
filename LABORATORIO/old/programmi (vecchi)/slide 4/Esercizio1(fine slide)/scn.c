#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//ssize_t write(int fildes, const void *buf, size_t nbytes);
//ssize_t read(int fildes, void *buf, size_t nbytes);
#define BUFFS 4096
//L'IMPUT DATO DALLA COMMAND SHELL DEVE ESSERE SENZA SPAZI E CON IL + OSSIA: 12+345

void freet(char *ris){
memset(ris,0,sizeof(ris));
}
void out(char *ris,char *c){
sprintf(ris,"%s ",c);
write(STDOUT_FILENO, ris, sizeof(ris));
freet(ris);
}
void out2(char *ris, int x){
sprintf(ris," %d",x);
write(STDOUT_FILENO, ris, sizeof(ris));
write(STDOUT_FILENO, "\n", sizeof(char));
freet(ris);
}


int main(void)
{
int n,i=0,k=-2,j=-1,l=0;
int x=0, y=0;
char buf[BUFFS];
char ris[999]="0";
while ((n=read(STDIN_FILENO, buf, BUFFS)) > 0){
            
            while(buf[i]){
                if(buf[i]!='+' && l==0)
                    j++;
                else if(buf[i]=='+'){l=1;}
                else k++;
                i++;
            }
            //out2(ris,j);out2(ris,k);

            i=0;
            while(buf[i]){
                if(buf[i]!='+' && j>=0){
                       x=x+((buf[i]-48)*pow(10,j));
                        //out2(ris,x);
                        j--;
                    }

                else if(buf[i]=='+'){
                        //out(ris,"+ \n");
                    }
                   
                else if(k>=0){
                        y=y+((buf[i]-48)*pow(10,k));
                        //out2(ris,y);
                        k--;
                    }

                i++;
            }



            //out2(ris,x);out2(ris,y);
            //freet(ris);
            x=x+y;
            out2(ris,x);

    if (write(STDOUT_FILENO, ris, sizeof(ris)) != sizeof(ris)){
        printf("write error");
    }

    if (n < 0){
    printf("read error");
    }
    write(STDOUT_FILENO, "\n", sizeof(char));

x=y=i=l=0;
j=-1;
k=-2;
freet(ris);
}
exit(0);
}
