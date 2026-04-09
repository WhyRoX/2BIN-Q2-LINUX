#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <string.h>

#include "utils.h"

#define BUFFER 50

void upper (char *str)
{
   int i = 0;
   while (str[i] != '\0') {
      str[i] = toupper(str[i]);
      i++;
   }
}

void child (void *argv) {

    int *pipefd = argv;
    char line[BUFFER + 1];

    sclose(pipefd[1]);

    int nbChar;
    while ((nbChar = sread(pipefd[0], line, BUFFER)) != 0) {
      printf("nbChar:: %d\n", nbChar);
      upper(line);
      nwrite(1, line, nbChar);
    }

    sclose(pipefd[0]);
}


int main(int argc, char **argv) {
    int fd1 = sopen(argv[1], O_RDONLY, 0644);

    int pipefd[2];
    spipe(pipefd);

    char line[BUFFER+2];

    fork_and_run1(child, pipefd);

    dup2(fd1, 0);

    sclose(pipefd[0]);

    // char* msg = "Write characts:\n";    
    // nwrite(1,msg,strlen(msg));


    int nbChar;
    while ((nbChar = sread(0, line, BUFFER)) != 0) {
      nwrite(pipefd[1], line, nbChar);
    }

    sclose(pipefd[1]);

}