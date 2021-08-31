#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 
#include <sys/wait.h>
#include <math.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <pthread.h>
#include <semaphore.h>

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "inserire nome al semaforo <name>");
        exit(-1);
    }
    sem_t * sem = sem_open(argv[1], O_CREAT | O_EXCL , S_IRUSR | S_IWUSR, 5);
    int val;
    sem_getvalue(sem, & val);
    printf("value semaphore = %d\n", val);
    sem_close(sem);
    sem_unlink(argv[1]);
    exit(0);
}
