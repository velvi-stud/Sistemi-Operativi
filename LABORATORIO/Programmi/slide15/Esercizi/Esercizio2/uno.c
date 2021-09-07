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
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <pthread.h>

typedef struct data{
    int start;
    int end;
}data;

char find;
char *namefile;
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER; 
int totount;

void *tf(void*arg){

    data d = *(data*)arg;
    
    /* riaprire il file perchè altrimenti la seek corrompe gli altri thread */
    FILE* inputFile2;
    if( ( inputFile2 = fopen( namefile, "r" ) ) == NULL ) {
		printf("Error- Unable to open\n");
		exit( -1 );
	}


    //printf("\n #### %ld controlla da: %d a %d",pthread_self(),d.start,d.end);
    
    int k=0, pos=d.start, count=0;
    char ch;

    fseek(inputFile2,d.start,SEEK_SET);

    while((ch=getc(inputFile2))){
        if (pos++>=d.end){
            break;
        }
        if(ch==find){
            count++;
        }
    }     

    // sezione critica per aggiungere valori alla variabile
    pthread_mutex_lock( & mymutex); // lock il mutex
    printf("\n @@@@ [%d] %ld ha trovato %d metch",pos,pthread_self(),count);
    totount+=count;
    pthread_mutex_unlock( & mymutex); // unlock mutex

}

int main(int argc, char const *argv[])
{
    if(argc<4){
        puts("\ninserire gli argomenti...\n");
        exit(3);
    }

    find = argv[3][0];
    namefile = (char*)argv[2];
    int x = atoi(argv[1]);

    /* first open file */ 
    FILE* inputFile;
    if( ( inputFile = fopen( namefile, "r" ) ) == NULL ) {
		printf("Error- Unable to open\n");
		exit( -1 );
	}
    /* check size (byte for char for thread)*/
    fseek(inputFile, 0, SEEK_END);    // Go to end
    int length = ftell(inputFile);   // read the position which is the size
    fseek(inputFile, 0, SEEK_SET);  // restore to start
    printf("\n Il file ha %d caratteri",length);
    int chpth = floor(length/x);
    printf(", quindi %d per thread\n",chpth);
    
    /* variabili per thread */
    pthread_t thread[x];
    data dati[x]; 
    int st=0, en=chpth;

    for (int i = 0; i < x; i++){
        /*controllo suddivisione e passo i limiti*/
        if (en>length) chpth=length;
        dati[i].start=st;
        dati[i].end=en;     
        /*inizializzo threads*/
        pthread_create(&thread[i],NULL,tf,&dati[i]);
        /*aggiorno variabili*/
        st = en;
        en += chpth;
    }

    /* aspetto terminazione */
    for (int i = 0; i < x; i++){
        pthread_join(thread[i],NULL);
    }

    printf("\n §§§§ CI SONO %d occorenze di %c",totount,find);
    
    printf("\n");
    return 0;
}
