    
    /* creare processo  (vfork lo esegue prima del padre) */
    int childpid= fork(); 
    
    /* attesa di un processo */
    waitpid(pid_process,&status,0);
    
    /* controllo che sia terminato normale */
    bool flag = WIFEXITED(status) 
    
    /* importo lo stato uscita del processo */
    WEXITSTATUS(status);
    
    
    /* terminare processo */
    exit(0);
    
    /* esecuzione exec con lista */
    execl("/bin/ps", "ps", "-elf", NULL);
    
    /* esecuzione programma c con arg e path*/
    char *env_init[]={"USER=sconosciuto", "PATH=/tmp", NULL}; 
    execle("/home/aulainfo/Scrivania/due.c", "arg 1", "arg 2", "arg 3", NULL, env_init);
    
    /* stessa cosa di prima ma il path è quello usato dall'invocante*/
    execlp("/home/aulainfo/Scrivania/due.c", "arg 1", "arg 2", "arg 3", NULL);
    
    
