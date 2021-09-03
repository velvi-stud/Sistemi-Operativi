// prende una stringa in argc e tramite la reverse (un'altra function prova8-1)
// USANDO LA MAKEFILE GENERARE UN OUTPUT
/* usaRev.c */
#include <stdio.h>
#include <string.h>
#include "reverse.h" /* contiene il prototipo di reverse */
/********************************************************/
int main (int argc, char *argv[]) {
/* Buffer per la stringa invertita */
char str[strlen(argv[1])+1];
/* Inverte la stringa in ingresso */
reverse (argv[1], str);
/* Mostra il risultato */
printf ("reverse (\"%s\") = %s\n", argv[1], str);
return 0;
}
