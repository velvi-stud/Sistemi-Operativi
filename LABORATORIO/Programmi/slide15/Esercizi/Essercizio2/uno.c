#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 
#include <sys/wait.h>
#include <math.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <pthread.h>

int fdf;
int N;
char *nome;
char patt;
int size;
int len;
int from=0;
int count=0;

//ho preferito non usare una struttura ma mettere le variabili globali poichè erano sempre gli stessi, cambiava solo size e count.
void *func (void *struct_arg){

    int i=0;
    int cnt=0;

    //salvo la posizione del byte di partenza lettura
    int start = from;

    //aggiorno la posizione dell'ultimo byte letto, ossia il primo byte da cui deve iniziare a leggere il prossimo thread
    from =from+len;

printf("\n------->thread %ld legge %d byte a partire dal byte %d, del size %d da leggere -> Counter= %d / %d\n\n",pthread_self(),len,start,size-len,count,cnt);

    //mi posiziono sull'esatto carattere da leggere
    if(lseek(fdf,start,SEEK_SET)<0){
        perror("errore seek");    
    }else{
        printf("-----------> sick at:%d",start);    
    }

    //setto la varabile buffer e leggo dal punto "start", "len"  caratteri.
    char buff[len+1]; buff[len+1]='\0';
    if(read(fdf,&buff,len)<0){
        perror("errore lettura");        
    }

    //eseguo il controllo dei caratteri
    while(buff[i]!='\0'||i<=len){
    //printf("%c",buff[i]);
        if(buff[i]==patt){
            cnt++;
        }
        i++;
    }
    printf("\n");

    //aggiorno il counter delle occorrenze 
    count=count+cnt;

    //chiudo
    pthread_exit(NULL);
}

int main(int argc, char*argv[]){

if(argc<4){
    printf("inserire il numero di thread da eseguire");
    exit(1);
}
N= atoi(argv[1]);
nome=argv[2];
patt= *argv[3]; 

//apro il file
fdf = open(nome,O_RDONLY);
if(fdf<0){
    perror("errore apertura file");
    exit(3);
}

// calcolo il size tramite la struct stat -> fstat
struct stat istic;
fstat(fdf,&istic);
size= istic.st_size;
len= ceil(size/N)+1;

printf("file aperto sul canale: %d. con size di: %d\n",fdf,size);

// creo i thread
pthread_t tid [N];
for(int i=0;i<N;i++){
    pthread_create(&tid[i],NULL,func,NULL);
    //pthread_join(tid[i],NULL);
}

// aspetto che i thread finiscano
for(int i=0;i<N;i++){
    pthread_join(tid[i],NULL);
}

close(fdf);

printf("il numero delle occorrenze è di: %d\n", count);
}
