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
#define READ 0 /* Estremità in lettura della pipe */ 
#define WRITE 1 /* Estremità in scrittura della pipe */

/*IL PROTOCOLLO UTILIZZATO E' 
LA PRIMA READ DICE IL NUMERO DI CARATTERI DELLA STRINGA 
LA SECONDA READ S' LA STRINGA INVIATA*/
 
char *msg[3] = { "Primo 12", "Secondo 24632", "Terzo 85875Hdkbd" };

int main (void) {
int i;
int fd [2];
int lengthsent; /* variabile per memorizzare la lunghezza messaggio*/
int bytesRead; /* variabile per memorizzare la lunghezza effettiva letta*/
char buffer [100]; /* Buffer del messaggio */ 
pipe (fd); /* Crea una pipe anonima */
if (fork() == 0){ /* Figlio, scrittore */
    close(fd[READ]); /* Chiude l’estremità inutilizzata */ 
    for (i = 0; i < 3; i++) {
        lengthsent=strlen(msg[i])+1 ; /* include \0 */ 
        write (fd[WRITE], &lengthsent, sizeof(int)); // gli invia prima il messaggio che indica la lunghezza della stringa
        write (fd[WRITE], msg[i], lengthsent); // gli invia il messaggio
    }
    close (fd[WRITE]); /* Chiude l’estremità usata */
}
else{ /* Genitore, lettore */
    close (fd[WRITE]); /* Chiude l’estremità non usata */ 
    while (read(fd[READ], &lengthsent, sizeof(int))) { // finchè riceve messaggio -> in questo caso riceve la lunghezza effettiva e la memorizza su una variabile intera
        bytesRead = read (fd[READ], buffer, lengthsent); // adesso legge il messaggio di byte pari alla lunghezza ricevuta dalla read di prima
        if (bytesRead != lengthsent) {
            printf("Errore!\n"); 
            exit(1);
        }
        printf("Padre-> Letti %d byte: %s\n",bytesRead,buffer);
    }
    close (fd[READ]); /* Chiude l’estremità usata */
}
exit(0);
}
