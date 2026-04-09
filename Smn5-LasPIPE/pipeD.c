#include <unistd.h>

#include "utils.h"

int main(int argc, char **argv) {
    int pipefd[2];
    spipe(pipefd);

    pid_t child1 = sfork();

    if (child1 != 0)
    {
        // pere
        pid_t child2 = sfork();

        if (child2 != 0)
        {
            sclose(pipefd[0]);
            sclose(pipefd[1]);
            swait(NULL);
            swait(NULL);
        }
    
        else {
            // fils2
            sclose(pipefd[1]);
            sdup2(pipefd[0], 0);

            execvp(argv[2], &argv[2]);
        }
        
    }

    else {
        // fils1
        sclose(pipefd[0]);
        sdup2(pipefd[1], 1);

        execlp(argv[1],argv[1],NULL);

    }
    
}