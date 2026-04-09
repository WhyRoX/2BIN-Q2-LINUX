#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"

int main(int argc, char **argv) {
    pid_t childId = sfork();

    if (childId != 0){} 
    else {
        while (true)
        {
            sleep(1000);
        }
    }
}