#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    int a = 5;
    int childId = fork();
    if (childId == -1)
    {
        perror("Child not good");
        return EXIT_FAILURE;
    }
    if (childId != 0)
    {
        int b = a * 5;
        printf("Parent = b = %d\n", b);
    }
    else
    {
        int b = a * 2;
        printf("Child = b = %d\n", b);
    }
    printf("FININSHED\n");
    return EXIT_SUCCESS;
}