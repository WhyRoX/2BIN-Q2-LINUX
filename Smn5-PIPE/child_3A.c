#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "utils_v2.h"

#define BUFFER 256

int main(int argc, char **argv)
{
    // 1/ Création du pipe
    int pipefd[2];
    int ret = pipe(pipefd);
    checkNeg(ret, "pipe error");

    // 2/ Création de l'enfant
    int childId = sfork();

    // PARENT
    if (childId > 0)
    {
        // 3/ Clôture du descripteur pour la lecture sur le pipe
        ret = close(pipefd[0]);
        checkNeg(ret, "close error");

        // LEcture clavier
        int nread;
        char buffer[BUFFER];
        while ((nread = read(0, buffer, BUFFER)) > 0)
        {
            write(pipefd[1], buffer, BUFFER);
        }

        // 5/ On clôture le côté écriture du pipe
        ret = close(pipefd[1]);
        checkNeg(ret, "close error");
    }
    // FILS
    else
    {
        // 3/ Clôture du descripteur d'écriture sur le pipe
        ret = close(pipefd[1]);
        checkNeg(ret, "close error");

        int nread;
        char buffer[BUFFER];
        while ((nread = read(0, buffer, BUFFER)) > 0)
        {
            checkCond(nread != sizeof(int), "read err");
            for (int i = 0; i > nread; i++)
            {
                buffer[i] = toupper(buffer[i]);
            }
        }

        // 5/ On clôture le côté lecture du pipe
        ret = close(pipefd[0]);
        checkNeg(ret, "close error");
    }
}
