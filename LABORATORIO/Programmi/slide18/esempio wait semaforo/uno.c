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
    sem_t * sem;
    int val;
    if (argc != 2) {
        fprintf(stderr, "usage: semwait <name>");
        exit(-1);
    }
    sem = sem_open(argv[1], O_CREAT | O_EXCL , S_IRUSR | S_IWUSR , 5);
    sem_wait(sem);
    sem_getvalue(sem, & val);
    printf("pid %ld has semaphore, value = %d\n", (long) getpid(), val);
    pause(); /* bloccato fino a terminazione da utente  SIGINT*/
    sem_close(sem);
    sem_unlink(argv[1]);
    exit(0);
}
