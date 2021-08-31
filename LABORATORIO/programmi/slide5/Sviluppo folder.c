    
    /* posizione corrente */
    char *cwd=getcwd(cwd,MAX_PATH);
    
    /* cambio cartella lavoro */
    chdir("/home/aulainfo/Scrivania/new_folder");
    
    /* controllo permessi lettura|scrittura|esecizione|esistenza */
    bool flag = access("./file.c", R_OK | W_OK | X_OK | F_OK);
    
    /* annulla i permessi che ci sono come argomento */
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    
    /* crea un file generico */
    creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
    
    /* aprire directory */
    DIR *cartella = opendir("/home/aulainfo/Scrivania/new_folder");
    
    /* usata sequenzialmente legge i contenuti della cartella */
    struct dirent *element = readdir(cartella);
    
    /*  */
