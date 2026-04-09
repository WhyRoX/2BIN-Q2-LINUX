#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "utils_v2.h"

volatile pid_t childId;

void sigusr1_handler(int sig) {}

void child_handler()
{
    while (true)
        sleep(1000);
}

int main()
{
    fork_and_run0(child_handler);
}