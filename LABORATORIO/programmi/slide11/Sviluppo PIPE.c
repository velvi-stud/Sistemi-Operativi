-----------------------> PIPE PER MESSAGGI

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
    while (read(fd[READ], &lengthsent, sizeof(int))) { // finchè riceve messaggio -> riceve la lunghezza effettiva e la memorizza su una variabile intera
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






-----------------------> PIPE PER SINCRONIZZAZIONE


#define READ 0
#define WRITE 1

//-> figlio2 -> padre -> figlio1 

int main(int argc, char *argv[]){
if(argc<2){
    printf("Inserire un pattern\n");
    exit(-2);
}else{
    if(strlen(argv[1])>=50){
        printf("size pattern eccessivo\n");   
        exit(-3); 
    }
}

int fd[2];
pipe(fd);
int child1 = fork();
if(child1==0){ // figlio 1 usa la grep <pat> delle cose lette dalla pipe -> aspetta che il padre scriva
    waitpid(getppid(),NULL,0);
    close(fd[WRITE]);
    dup2(fd[READ],READ);
    close(fd[READ]);
    printf("figlio 1\n");
    execlp("grep","grep",argv[1],NULL);
    
    exit(42);
}
else{ //padre usa la ls -R  e scrive sulla pipe
    int ad[2];
    pipe(ad);
    int child2 = fork();
    if(child2==0){ // figlio 2 usa la ls -l e manda direttamente il messaggio al padre
        close(ad[READ]);
        dup2(ad[WRITE],WRITE);
        close(ad[WRITE]);
        printf("figlio 2\n");
        execlp("ls","ls","-l",NULL);
        
        exit(43);
    }
    else{ // padre usa la sort -> aspetta che il figlio 2 scriva sullo STDOUT e manda il risultato la figlio 1
        close(ad[WRITE]);
        close(fd[READ]);
        dup2(ad[READ],READ);
        dup2(fd[WRITE],WRITE);
        close(ad[READ]);
        close(fd[WRITE]);
        printf("padre\n");
        execlp("sort","sort",NULL);
        
        exit(54);
    }
}
return 0;
}







