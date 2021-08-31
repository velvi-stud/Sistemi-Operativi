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
        fprintf(stderr, "usage: sempost <name>");
        exit(-1);
    }
    sem = sem_open(argv[1], O_CREAT | O_EXCL , S_IRUSR | S_IWUSR , 5);
    sem_post(sem);
    sem_wait(sem);
    sem_wait(sem);
    sem_wait(sem);
    sem_getvalue(sem, & val);
    printf("value = %d\n", val);
    sem_close(sem);
    sem_unlink(argv[1]);
    exit(0);
}
