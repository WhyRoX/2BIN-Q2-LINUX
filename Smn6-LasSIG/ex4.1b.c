#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"

static const char *const HELLO = "Hello, je suis le sigusr1_handler ; SUGUSR1 recu!\n";

void sigusr1_handler (int sig) {
  const size_t sz = strlen(HELLO);   // async-signal-safe function
  write(1, HELLO, sz);               // async-signal-safe function
  
  _exit(10);  // async-signal-safe function
}

int main(int argc, char **argv) {

    ssigaction(SIGUSR1, sigusr1_handler);

    pid_t childId = sfork();

    if (childId != 0){
        //pere
        usleep(1);
        printf("[Pere %d] envoi du signal SIGUSR1 à mon fils %d\n", getpid(), childId);
        skill(childId, SIGUSR1);
        int statut;
        swaitpid(childId, &statut, 0);
    } 
    else {
        //fils
        pause();
        exit(0);
    }
}