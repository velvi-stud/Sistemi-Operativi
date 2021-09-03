
    /* aprire */
    fds = open("./nome_file",  O_CREAT | O_WRONLY |  O_RDONLY | O_TRUNC | O_APPEND, 0777);
    
    /* posizionarsi all'interno del file*/
    lseek(fds, 1, SEEK_CUR);    /*Si posiziona alla fine del file*/ 

    /* leggere */
    read(fds, &buff, sizeof(char));
    
    /* scrivere */
    write(fdd, &buff, sizeof(char));
    
    /* chiudere */
    close(fds);
    
    /* Effettua una copia di fds sul file descriptor fd2*/
    fd2 = dup (fds);  
    
    /* Duplica il canale 3 sul canale 2 */
    dup2 (3, 2);	
