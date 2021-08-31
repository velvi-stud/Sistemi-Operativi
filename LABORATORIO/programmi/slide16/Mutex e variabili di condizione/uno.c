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

struct msg {
    struct msg * m_next;
    /* … altra roba … */
};

struct msg * workq;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void) {
    struct msg * mp;
    while (1) {
        pthread_mutex_lock( & qlock);
        while (workq == NULL)
            pthread_cond_wait( & qready, & qlock);
        mp = workq;
        workq = mp -> m_next;
        pthread_mutex_unlock( & qlock);
        /* ora elabora il messaggio mp */
    }

}

void enqueue_msg(struct msg * mp) {
    pthread_mutex_lock( & qlock);
    mp -> m_next = workq;
    workq = mp;
    pthread_mutex_unlock( & qlock);
    pthread_cond_signal( & qready);
}
