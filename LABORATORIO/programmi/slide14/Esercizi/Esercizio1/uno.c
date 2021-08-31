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

int A,B,x;

void cubo(int sign) {
    printf("A-> calcolo il cubo del numero : %d\n", x * x * x);
}

void adios(int sign) {
    printf("B-> Arrivederci.\n");
}

void message(int sign) {
    printf("A-> messaggio!\n");
    exit(0);
}

void reciproco(int sign) {
    printf("B-> Reciproco di %d : 1/%d\n Aspetto: %d secondi...\n", x, x, 2 * x);
    sleep(2 * x);
    kill(A, SIGUSR1);
    exit(0);
}

int main(int argc, char * argv[]) {
    x = atoi(argv[1]);
    A = fork();
    if (A == 0) {
        printf("A-> Sono %d \n", getpid());
        if (x % 2 == 0) {
            signal(SIGUSR1, cubo);
            pause();
        } else {
            signal(SIGUSR1, message);
            pause();
        }
    } 
    else {
        B = fork();
        if (B == 0) {
            printf("B-> Sono %d \n", getpid());
            if (x % 2 == 0) {
                signal(SIGUSR1, adios);
                pause();
                exit(1);
            } 
            else {
                signal(SIGUSR2, reciproco);
                pause();
            }
        } 
        else {
            //printf("padre-> Sono %d \n", getpid());
            if (x % 2 == 0) {
                sleep(1);
                printf("main-> Numero pari.\n");
                kill(A, SIGUSR1);
                waitpid(A, NULL, 0);
                kill(B, SIGUSR1);
                waitpid(B, NULL, 0);
            } 
            else {
                sleep(1);
                printf("main-> Numero dispari.\n");
                kill(B, SIGUSR2);
                waitpid(A, NULL, 0);
                waitpid(B, NULL, 0);
            }
        }
    }
    exit(0);

}
