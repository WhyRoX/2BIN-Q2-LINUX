#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "testmult.h"
#include "utils_v1.h"

/* Return a random number between 1 and 9 */
int alea()
{
    int c = (int)((double)rand() / (RAND_MAX) * (10 - 1)) + 1;
    return c;
}

//TODO

int main(int argc, char **argv)
{

    // TODO

}
