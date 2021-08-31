    
    /* creare fifo */
    mkfifo("./esempio_fifo", 0777); 
    
    /* aprire fifo */
    int fifo_fd = open("./esempio_fifo", O_WRONLY | O_RDONLY);
    
    /* scrivere sulla fifo */
    write(fifo_fd, buffer, BUFFER_SIZE);
    
    /* leggere sulla fifo */
    read(fifo_fd, buffer, BUFFER_SIZE);
    
    /* chiudere fifo */
    close(fifo_fd);
