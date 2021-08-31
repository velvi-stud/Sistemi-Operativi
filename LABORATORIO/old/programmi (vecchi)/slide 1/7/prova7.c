// controlla i vari errore input: codice  output: decrizione
#include<errno.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]){
// err_no 5 = EIO -> input/output error
int ee=5;
//metodo stampa 1
fprintf(stderr, "EACCES con numero: %s\n", strerror(ee));
fprintf(stderr, "EACCES con codice: %s\n", strerror(EIO));
//metodo stampa 2
errno = EIO;
perror(argv[0]);
/*
oppure errori tipo:
#define EPERM            1       Operation not permitted
#define ENOENT           2       No such file or directory
#define ESRCH            3       No such process
#define EINTR            4       Interrupted system call
#define EIO              5       I/O error
#define ENXIO            6       No such device or address
#define E2BIG            7       Arg list too long
#define ENOEXEC          8       Exec format error
#define EBADF            9       Bad file number
#define ECHILD          10       No child processes
#define EAGAIN          11       Try again
#define ENOMEM          12       Out of memory
#define EACCES          13       Permission denied
#define EFAULT          14       Bad address
#define ENOTBLK         15       Block device required
#define EBUSY           16       Device or resource busy
#define EEXIST          17       File exists
*/
return(0);
}
//1-40
