/* poichè non è possibile passare più di un parametro, si usa la struct. È una variabile, quindi è solo un parametro, ma al suo interno ci possono essere più varabili*/
struct struttura {
    char var1;
    int var2;
    bool var3;
    float var4;
};

/* funzione che sarà eseguita dai thread */
void *char_print (void* parameters) { 

    /* cast del puntatore al tipo corretto, essendo dato un void */
    struct struttura *p = (struct struttura*) parameters;  
    
    /* elabora i dati passati dalla struct */
    p->var2++;
    p->var4+=1.42455;
    p->var3=false;
        
    /* temina l'esecuzione*/
    pthread_exit((void *) p->var2);
}

int main() {

    /* variabile identificativa dei thread*/
    pthread_t tid[2];
    
    /* poichè i dati possono essere passati tramite struct: */
    struct struttura tid1_args;
    struct struttura tid2_args;

    /* assegno variabili all'interno della struttura tid1_args */
    tid1_args.var1 = '0';
    tid1_args.var4 = 304.400;

    /* assegno variabili all'interno della struttura tid2_args */
    tid2_args.var2 = '1';
    tid2_args.var4 = 242.500;
    
    /* creo e attivo il thread1 e thread2  (notare il passaggio del parametro)*/
    pthread_create( &tid[0] , NULL , char_print , (void*) &tid1_args); 
    pthread_create( &tid[1] , NULL , char_print , (void*) &tid2_args); 

    /* aspetto che termino l'esecuzione */
    void *rit1, *rit2;
    pthread_join(tid[0], &rit1);
    pthread_join(tid[1], &rit2);
    
    /* aspetta che i thread finiscano prima di chiudere il programma */
    // se dovesse chiudersi prima dell'esecuzione dei thread allora questi non verranno mai eseguiti
    sleep(1);
    return 0;
}
