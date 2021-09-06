#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "apue.h"

#define PATH_MAX 4096

int main(void) {
	
	umask(0);

    char * currentfolder = malloc(PATH_MAX);
    
    getcwd(currentfolder, PATH_MAX);

    /* creo cartella corrente "/bar" */
    strcat(currentfolder, "/");
    char * namenewfolder = "bar";
  	char * fold= strcat(currentfolder, namenewfolder);
  	
  	// se esiste la cencello
  	rmdir(fold);
    
    // creo cartella e assegno permessi a tutti
    mkdir(fold, 0777);

    /* cambio permessi a "bar" da rwx-rwx-rwx to "rw-r--r--" */
    chmod(namenewfolder, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    /* apre lo stat di "foo" per gli st_mode */
    struct stat statbuf;
    stat("foo", & statbuf);

    /* impostai suoi vecchi permessi ed inserisce il set-group-ID e disattiva group-execute */
    chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID);

    exit(0);
}
