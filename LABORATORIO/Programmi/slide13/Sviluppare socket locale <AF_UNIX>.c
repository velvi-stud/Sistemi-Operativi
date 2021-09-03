----------------> CLIENT

    /* defiamo il descrittore alla soket | il client possa connettersi con il server */
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    /* variabile usata per dare un nome alla socket */ 
    struct sockaddr_un address; 

    /* definiamo il tipo -> usando una struct sockaddr_un è logico che sia AF_UNIX */
    address.sun_family = AF_UNIX; 
    
    /* nome della socket che si utilizza per la connessione al server, ovviamente il server deve avere lo stesso */
    strcpy(address.sun_path, "./server_socket"); 
    
    /* connettiamo la nostra socket con quella del server e controlla la connessionee*/
    connect(sockfd, (struct sockaddr*) &address, sizeof(address)); 
    // DA NOTARE che si usa (struct sockaddr *) &address per rendere compatibile il tipo passato, da struct sockaddr_UN a sockaddr (anche avendo gli stessi campi)

    /* possiamo leggere e scrivere via sockfd */
    write(sockfd, &var, sizeof(var));
    read(sockfd, &buf, sizeof(buf));
    
    /* una volta finito chiude la socket */
    close(sockfd);
    
    /* termina */
    exit(0);


-----------------> SERVER
    
    /* defiamo il descrittore alla soket | il client possa connettersi con il server */
    int server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    /* variabile usata per dare un nome alla socket */ 
    struct sockaddr_un server_address;
    
    /* definiamo il tipo -> usando una struct sockaddr_un è logico che sia AF_UNIX */
    server_address.sun_family = AF_UNIX;
    
    /* nome della socket che si ha intenzione di dargli (il nome deve essere comune anche al client) */
    strcpy(server_address.sun_path, "./server_socket");
    
    /* l'equivalente della connect del client ma in questo caso la sto creando non connettendo */
    bind(server_sockfd, (struct sockaddr *) &server_address, sizeof(server_address));
    
---> ACCETTARE CONNESSIONE 

    /* possono esserci massimo 5 processi richiedenti contemporaneamente */
    listen(server_sockfd, 5);
    
    /* ovvaimente fatto tutto in un ciclo */
    while (1) {
        
        /* variabile usata per dare un nome alla socket */
        struct sockaddr_un client_address;
        
        /* identifica la lunghezza della socket */
        client_len = sizeof(client_address);
  
        /* accetta la connessione proveniente dalla socket server_sockfd, e utilizza i canale di comunicazione client_address avente lunghezza client_len per connettersi e "parlare" con il client */
        int client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len); 

        /* possiamo leggere e scrivere via sockfd */
        write(sockfd, &var, sizeof(var));
        read(sockfd, &buf, sizeof(buf));
        
        close(client_sockfd); // chiude la socket aperta per il client
    }

    /* una volta finito chiude la socket */
    close(sockfd);
    
    /* termina */
    exit(0);





