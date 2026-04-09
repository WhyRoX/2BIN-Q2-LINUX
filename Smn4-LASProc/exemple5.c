/// version du programme utilisant une des fonctions fork_and_run() 
/// fournies dans le module utils. Elles permettent de séparer le code
/// du père (main) et le code du fils (fonction séparée, fournie en  
/// argument de fork_and_run).

/// Notez que argv[0] n'est plus directement accessible dans
/// le processus fils (implémenté par la fonction childProcess()) ;
/// argv[0] est donc fourni en paramètre à la fonction childProcess() 
/// (étant de type générique void*, il doit être casté en char*) et
/// et le processus fils est créé grâce à la fonction fork_and_run1() 
/// qui a un unique paramètre.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"

void childProcess(void *name)
{
  /* Dans le processus fils */
  char *pgm = name;
  colorOn(1,YELLOW_TEXT);
  printf("Je suis le fils '%s': pid=%i - ppid=%i\n", pgm, getpid(), getppid());
  sexecl("./myScript.sh", "myScript.sh", NULL);
}

int main(int argc, char **argv)
{
  /* Création d'un processus fils */
  int childId = fork_and_run1(childProcess, argv[0]);

  /* Dans le processus parent */
  colorOn(1,PURPLE_TEXT);
  printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i)\n",getpid(),childId);

  /* Attente de la terminaison du processus fils */
  int status;
  swaitpid(childId, &status, 0);
  
  colorOn(1,PURPLE_TEXT);
  printf("Processus parent se termine après son enfant (pid fils=%i)\n",childId);
}