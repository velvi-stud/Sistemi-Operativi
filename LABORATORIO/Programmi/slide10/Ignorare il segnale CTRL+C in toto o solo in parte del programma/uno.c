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
#include <signal.h>
// blocco sempre
/*
int main(void)
{
signal (SIGINT, SIG_IGN); 
while (1) pause();
}
*/

// oppure per bloccare il blocco del programma in una operazione critica

static void oldHandler(int signo){ // operazione alla ricezione di una kill 
printf("\n segnale ricevuto \n"); 
return; 
}

int main (void) { 
//void (*oldHandler) (int); // vecchio handler 
printf ("Posso essere interrotto\n"); 
sleep (3); 
signal (SIGINT, SIG_IGN); // Ignora Ctrl-c 
printf ("Ora sono protetto da Control-C\n"); 
sleep (3); 
signal (SIGINT, oldHandler); // Ripristina il vecchio handler  
printf ("Posso essere interrotto nuovamente\n"); 
sleep (3); 
printf ("Ciao!\n"); 
return 0; 
}

