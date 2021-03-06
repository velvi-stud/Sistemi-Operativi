#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h" 

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("inserire gli argomenti in input al file .out \n");
        return (333);
    }
    
    DIR * cartella = opendir(argv[1]);
    
    if (cartella == NULL) {
        perror("opendir error");
        exit(432);
    }
    
    struct dirent * element;
    
    while ( (element = readdir(cartella)) != NULL) {// ogni iterazione la readdir esegue la seek su un altro elemento
        printf("%s -- ", element -> d_name);
        printf("%ld\n", element -> d_ino);
    } 	
        
	closedir(cartella);	    
    
    return 2;
}
