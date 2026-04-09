#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "utils.h"

int main(int argc, char **argv)
{
    // char *str1 = "trois .. deux .. un ..\n";
    // char *str2 = "partez !\n";

    //swrite(1, str1, strlen(str1));
    // sans \n bufferisation donc on affiche deux fois, avec \n on séprare \n vide le buffer
    printf("trois .. deux .. un ..");

    int childId = sfork();

    if (!childId) { 
        //swrite(1, str2, strlen(str2));
        printf("partez !");

    }
}