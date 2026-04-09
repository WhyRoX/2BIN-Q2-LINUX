#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "utils.h"

#define MAXCHAR 80

int main(int argc, char *argv[]) {
    if (argc != 3)
    {
        printf("Usage: %s", argv[0]);
        perror("not enough args");
    }

    char BUFFER[MAXCHAR+1];
    int fd1,fd2;

    fd1 = sopen(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    fd2 = sopen(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);

    int nbCharRd, nbCharWr;

    while((nbCharRd = read(0, BUFFER, MAXCHAR+1))) {
        checkNeg(nbCharRd,"Error reading stdin1");
        if (BUFFER[nbCharRd-1] == '\n')
        {
            BUFFER[nbCharRd]='\0';
            if (isupper(BUFFER[0]))
            {   
                nbCharWr = swrite(fd1, BUFFER, nbCharRd);
                checkCond(nbCharWr != nbCharRd, "Error writing file");
            }
            else if (islower(BUFFER[0]))
            {
                nbCharWr = swrite(fd2, BUFFER, nbCharRd);
                checkCond(nbCharWr != nbCharRd, "Error writing file");
            }
            else {
                while ((nbCharRd = read(0,BUFFER,MAXCHAR+1)) > 0 && (BUFFER[nbCharRd-1] != '\n'))
                checkNeg(nbCharRd,"Error reading stdin");
                perror("ligne pas good, stdin emptied?");
            }
        }
    }

    checkNeg(close(fd1), "Error CLOSE");
    checkNeg(close(fd2), "Error CLOSE");
}