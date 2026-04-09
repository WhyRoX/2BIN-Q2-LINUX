#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    printf("trois .. deux .. un ..\n");

    int childId = fork();
    if (childId == -1)
    {
        perror("Child not good");
        exit(0);
    }
    if (childId != 0)
    {
        printf("partez !\n");
    }

    exit(0);
}