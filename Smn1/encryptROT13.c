#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "cryptROT13.h"
#include <string.h>

int main(int argc, char const *argv[])
{
    char* buffer = readLine();

    if (buffer == NULL)
    {
        printError("Error: readLine() failed\n");
        exit(1);
    }
    

    buffer = encrypt(buffer);
    buffer[strlen(buffer)] = '\n';
    printOk(buffer);
    free(buffer);
    exit(0);
}
