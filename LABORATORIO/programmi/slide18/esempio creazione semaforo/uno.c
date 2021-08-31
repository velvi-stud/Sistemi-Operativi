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

#define FILE_MODE S_IRUSR | S_IWUSR

int main(int argc, char ** argv) {
    int c, flags;
    sem_t * sem;
    unsigned int value;
    flags = O_CREAT;
    value = 1;
    while ((c = getopt(argc, argv, "ei:")) != -1) {
        switch (c) {
        case 'e':
            flags |= O_EXCL;
            break;
        case 'i':
            value = atoi(optarg);
            break;
        }
    }
    if (optind != argc - 1) {
        fprintf(stderr, "usage: semcreate [-e] [-i initialvalue] <name>");
        exit(-1);
    }
    sem = sem_open(argv[optind], flags, FILE_MODE, value);
    sem_close(sem);
    exit(0);
}
