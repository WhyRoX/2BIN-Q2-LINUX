/// version du programme utilisant un script bash (contenant la commande "ps -l")
/// et l'appel système waitpid (au lieu de wait)

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
    int status;   // statut de l’enfant terminé
    int waitId = waitpid(childId, &status, 0);   // waitId = pid renvoyé par le wait (=childId)
    checkCond(waitId == -1, "Wait error");
    
    colorOn(1,PURPLE_TEXT);
    printf("Processus parent se termine après son enfant (pid fils=%i)\n",childId);
  } 
  else 
  { 
    /* Dans le processus fils */
    colorOn(1,YELLOW_TEXT);
    printf("Je suis le fils '%s': pid=%i - ppid=%i\n",argv[0],getpid(),getppid());
    execl("./myScript.sh","myScript.sh", NULL);
    checkCond(true, "Exec failed");
  }
}