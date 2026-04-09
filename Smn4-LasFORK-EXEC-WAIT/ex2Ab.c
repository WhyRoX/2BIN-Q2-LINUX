#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    char *msg = "trois .. deux .. un ..\n";
    int len = strlen(msg);
    ssize_t nbCharWr = write(1, msg, len);
    if (nbCharWr != len)
    {
        exit(0);
    }

    int childId = fork();
    if (childId == -1)
    {
        perror("Child not good");
        exit(0);
    }
    if (childId != 0)
    {
        char *msg = "partez !\n";
        int len = strlen(msg);
        ssize_t nbCharWr = write(1, msg, len);
        if (nbCharWr != len)
        {
            exit(0);
        }
    }

    exit(0);
}