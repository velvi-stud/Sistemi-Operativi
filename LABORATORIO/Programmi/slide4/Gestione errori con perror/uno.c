#include <stdio.h> 
#include <fcntl.h> 
#include <errno.h> 
int main(void) { 
int fd;
fd = open ("nonexist.txt", O_RDONLY); /* Apre un file inesistente per causare un errore */ 
if (fd == -1) { /* fd=-1 => si è verificato un errore nella open*/ 
printf ("errno = %d\n", errno);
perror ("main");
}

fd = open ("/", O_WRONLY); /* Forza un errore diverso */ 
if (fd == -1) { /* fd=-1 => si è verificato un errore nella open*/
printf ("errno = %d\n", errno); 
perror ("main");
}

fd = open ("nonexist.txt", O_WRONLY | O_CREAT, 0644); /* Esegue una system call con successo */
printf("errno = %d\n", errno);

perror ("main"); /* Visualizza dopo la chiamata */

errno = 0; /* Reset manuale variabile di errore */

return 0;
}
