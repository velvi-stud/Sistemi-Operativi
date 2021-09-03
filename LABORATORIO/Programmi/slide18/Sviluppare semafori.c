--------> Basati su nome

    sem_t * sem= sem_open(nome_semaforo, O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR, max_number);
    
    sem_wait(sem);
    
    sem_post(sem);
    
    sem_getvalue(sem, &val);
    
    sem_close(sem);
    
    sem_unlink(nome_semaforo);
    
    
--------> Basati su memoria

    sem_init( &nome_semaforo, 0, max_number);
    
    sem_wait(sem);
    
    sem_post(sem);
    
    sem_destroy( &nome_semaforo );
