----------> MUTEX

    /* inizializza il mutex globalmente*/
    pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER; 

    /* per bloccare il mutex */
    pthread_mutex_lock( & mymutex); // lock il mutex
    
    /* per sbloccare il mutex */    
    pthread_mutex_unlock( & mymutex); // unlock mutex

----------> VARABILI CONDIZIONE
    
    /* inizializza la variabile di condizione globalmente*/
    pthread_cond_t mycond = PTHREAD_COND_INITIALIZER; 

    /* bloccare con la varabile di condizione */
    pthread_cond_wait( &mycond, &mymutex );
    
    /* per sbloccare la condizione */    
    pthread_cond_signal( &mycond);
