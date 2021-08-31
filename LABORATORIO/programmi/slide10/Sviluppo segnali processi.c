    
    /* assegna gestore segnale */
    signal(SIGUSR1, sig_usr);
    
    /* ignorare segnale */
    signal (SIGINT, SIG_IGN);
    
    /* gestore segnale */
    static void sig_usr(int signo){ ... }
    
    /* invio segnali IPC*/
    kill (pid_process, SIGINT);
