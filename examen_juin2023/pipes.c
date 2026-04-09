#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils_v2.h"

#define BUFFER_SIZE 80

void child(void *pipe1, void *pipe2);

int main(int argc, char **argv)
{
    int fathToChild[2];
    int childToFath[2];
    char ligne[BUFFER_SIZE+1];
    int nbChar;
    int countChar;
    int nbLines;

    spipe(fathToChild);
    spipe(childToFath);

    fork_and_run2(child, fathToChild, childToFath);

    sclose(fathToChild[0]);
    sclose(childToFath[1]);

    while ((nbChar = sread(0, ligne, BUFFER_SIZE)) > 0)
    {
        ligne[nbChar-1] = '\0';
        swrite()
    }

}

void child(void *pipe1, void *pipe2)
{
    int *fathToChild = (int *)pipe1;
    int *childToFath = (int *)pipe2;
    int nbLines = 0;
    int nbChar;
    char ligne[BUFFER_SIZE];

    sclose(fathToChild[1]);
    sclose(childToFath[0]);
    dup2(fathToChild[0], 0);
    dup2(childToFath[1], 1);

    while(1)
    {
        nbChar = sread(0, ligne, BUFFER_SIZE);

        if (nbChar==0)
        {
            swrite(1, &nbLines, sizeof(int));
            break;
        }
        swrite(1, &nbChar, sizeof(int));
        nbLines++;
    }
    sclose(0);
    sclose(1);
}
