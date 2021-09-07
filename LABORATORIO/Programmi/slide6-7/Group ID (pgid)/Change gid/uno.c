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
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

/*
    Cambio group id dei processi
*/


int main() {

  pid_t pid;

  char c='?'; // char a caso

    int p1[2], p2[2]; // pipe per la sincronizzazione
    pipe(p1);
    pipe(p2);

    if ((pid = fork()) == 0) { // processo figlio

      printf("child's process group id is %d\n", (int) getpgrp());
      
      write(p2[1], &c, 1); // sblocca processo padre
      
      printf("child is waiting for parent to complete task\n");

      read(p1[0], &c, 1); // attende processo padre
      
      printf("child's process group id is now %d\n", (int) getpgrp());
      
      exit(0);

    }

    else { // processo padre
      
      printf("parent's process group id is %d\n", (int) getpgrp());
      
      read(p2[0], &c, 1); // attende processo figlio

      printf("parent is performing setpgid() on pid %d\n", (int) pid);
      
      setpgid(pid, 0); // cambia gid del figlio
      
      write(p1[1], &c, 1); // sblocca processo figlio
      
      printf("parent's process group id is now %d\n", (int) getpgrp());
      
      sleep(5);
    }
}