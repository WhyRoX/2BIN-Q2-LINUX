#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"

static const char HELLO[] = "signal SIGUSR1 recu !\n";
volatile sig_atomic_t cpt = 0;
volatile sig_atomic_t end = 0;


void sigchld_handler (int sig) {
  end = 1;
}

void sigusr1_handler (int sig) {
  write(STDOUT_FILENO, HELLO, sizeof(HELLO) - 1);
   cpt++;
  if (cpt == 7)
  {
    printf("Fin du fils. J'ai utilise mes 7 vies...\n");
    _exit(0);
  }
}

//***************************************************************************//
// CHILD CODE
//***************************************************************************//

void child_handler () {
  /* PROCESSUS ENFANT */

  while (true) { // was while (cpt<7) but actually while true reald cond is in sighandler
    pause();
  }
}

//***************************************************************************//
// MAIN
//***************************************************************************//

int main () {
  ssigaction(SIGUSR1, sigusr1_handler);
  ssigaction(SIGCHLD, sigchld_handler);

  pid_t childId = fork_and_run0(child_handler);

  int nbSent = 0;

  printf("[Pere %d] envoi du signal SIGUSR1 a mon fils %d\n", getpid(), childId);
  while (end != 1) {
    skill(childId, SIGUSR1);
    nbSent++;
  } 

  int statut;
  swaitpid(childId, &statut, 0);
  if (WIFEXITED(statut)) {
    printf("Fin du pere. %d SIGUSR1 envoyes.\n", nbSent);
  }

  return 0;
}