#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h>
int main (void) { 
int fd1, fd2, fd3;

fd1 = open ("test.txt", O_CREAT | O_RDWR, 0600); 
printf ("fd1 = %d\n", fd1);
write (fd1, "Cosa sta", 8);

fd2 = dup (fd1); /* Effettua una copia di fd1 sul descriptor fd2*/ 
printf ("fd2 = %d\n", fd2);
write (fd2, " accadendo", 10);

close (0);	/* Chiude lo standard input */
fd3 = dup (fd1); /* Effettua un’altra copia di fd1 e poichè esegue lo scanner dal file descriptor 0 e controlla che siano disponibili, e poichè abbiamo chiuso il canale 0 prenderà questo*/ 
printf ("fd3 = %d\n", fd3);
write (0, " al contenuto", 13);

dup2 (3, 2);	/* Duplica il canale 3 sul canale 2 */
write (2, "?\n", 2);

return 0;
}
