/* Envoi d'un signal SUGUSR1 du processus père à son fils.
   Le fils se met en attente d'un signal avec le syscall pause() */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils_v2.h"

//***************************************************************************//
// SIGUSR1 handler (fils)
//***************************************************************************//

static const char *const HELLO = "Hello, je suis le sigusr1_handler ; SUGUSR1 recu!\n";

/* Note: les écritures write() ne sont pas testées ici car
   un handler de signaux n'est pas censé réaliser des opérations IO ;
   nous faisons ces écritures dans le cadre de ce cours pour
   faciliter la compréhension des gestionnaires de signaux */
void sigusr1_handler(int sig)
{
  const size_t sz = strlen(HELLO); // async-signal-safe function
  write(1, HELLO, sz);             // async-signal-safe function

  _exit(10); // async-signal-safe function
}

//***************************************************************************//
// MAIN
//***************************************************************************//

int main()
{
  // initialisation de la structure sigaction à 0
  struct sigaction action = {0};
  // définition du handler de SIGUSR1
  action.sa_handler = sigusr1_handler;
  // armement du signal SUGUSR1
  int ret = sigaction(SIGUSR1, &action, NULL);
  checkNeg(ret, "erreur sigaction 1");

  pid_t childId = sfork();
  if (childId == 0)
  {
    /* PROCESSUS FILS */
    printf("[Fils %d] j'attends un signal de mon pere %d\n", getpid(), getppid());

    // attente d'un signal
    pause();
    exit(0);
  }

  /* PROCESSUS PARENT */
  usleep(1000); // pour forcer le passage de main au fils et s'assurer qu'il ait le temps de s'initialiser
  printf("[Pere %d] envoi du signal SIGUSR1 à mon fils %d\n", getpid(), childId);

  // envoi de signal SIGUSR1 au processus fils
  ret = kill(childId, SIGUSR1);
  checkNeg(ret, "erreur kill SIGUSR1");

  // attente de la terminaison du fils
  int statut;
  swaitpid(childId, &statut, 0);
  if (WIFEXITED(statut))
    printf("[Pere %d] Mon fils %d s'est terminé avec le statut: %d\n", getpid(), childId, WEXITSTATUS(statut));
}
