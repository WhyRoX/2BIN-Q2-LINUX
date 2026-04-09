/// programme créant un processus fils pour exécuter la commande "ps -l"
/// il utilise les appels système fork, wait et execl,
/// ainsi que les fonctions "check..." du module utils

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"

int main(int argc, char **argv) 
{
  /* Création d'un processus fils */
  int childId = fork();
  checkCond(childId == -1, "Fork failed");

  if (childId != 0)   // childId = pid de l’enfant
  {  
    /* Dans le processus parent */
    colorOn(1,PURPLE_TEXT);
    printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i)\n",getpid(),childId);

    /* Attente de la terminaison du processus fils */
    int waitId = wait(NULL);   // waitId = pid renvoyé par le wait (=childId)
    checkCond(waitId == -1, "Wait error");
    
    colorOn(1,PURPLE_TEXT);
    printf("Processus parent se termine après son enfant (pid fils=%i)\n",childId);
  } 
  else 
  { 
    /* Dans le processus fils */
    colorOn(1,YELLOW_TEXT);
    printf("Je suis le fils '%s': pid=%i - ppid=%i\n",argv[0],getpid(),getppid());
    execl("/usr/bin/ps", "ps", "-l", NULL);
    checkCond(true, "Exec failed");
  }
}