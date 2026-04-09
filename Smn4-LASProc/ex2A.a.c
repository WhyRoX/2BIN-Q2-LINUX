#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"

int main(int argc, char **argv) {

    int a = 5;

    int childId = sfork();

    printf("childId = %i\n", childId);

    if (childId != 0) {
        int b = a * 5;
        printf("parent process : a*5 = %d\n", b); 
    } else {
        int b = a * 2;
        printf("child process : a*2 = %d\n", b);
    }
}