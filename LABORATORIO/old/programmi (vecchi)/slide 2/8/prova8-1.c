//funzione reverse di due stringhe -> IMPLEMENTAZIONE
/* prova8-1.c */
#include <stdio.h>
#include <string.h>
/*******************************************************/
void reverse ( char *before, char *after ) {
/* before: puntatore alla stringa originaria */
/* after: puntatore alla stringa invertita */
int i, j, len;
len = strlen (before);
for (j=len-1, i=0; j>=0; j--, i++) /* Ciclo */
after[i] = before[j];
after[len] = '\0';
/* \0 termina la stringa invertita */
}
