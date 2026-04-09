/* Accès à une shm contenant 1 entier, partagée entre 
   un processus père et son fils. On donne au fils
   la responsabilité de créer et initialiser la shm.
   Le père lit puis détruit la shm.
   Utilisation des fonctions shm du module utils. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "utils.h"

#define KEY 369
#define PERM 0666

//******************************************************************************//
// CHILD HANDLER
//******************************************************************************//
void child_handler()
{
  // CREATE & ATTACH SHARED MEMORY
  int shm_id = sshmget(KEY, sizeof(int), IPC_CREAT | PERM);
  int *z = sshmat(shm_id);

  // ACCESS SHARED MEMORY
  printf("IN CHILD: shared mem value: *z = %d\n", *z);
  *z = 987654321;
  
  // DETACH SHARED MEMORY
  sshmdt(z);
}

//******************************************************************************//
// MAIN FUNCTION
//******************************************************************************//
int main(int argc, char *argv[])
{
  pid_t cpid = fork_and_run0(child_handler);

  swaitpid(cpid, NULL, 0); // make sure child finishes before accessing shared memory

  // GET & ATTACH SHARED MEMORY
  int shm_id = sshmget(KEY, sizeof(int), 0);
  int *z = sshmat(shm_id);

  // ACCESS SHARED MEMORY
  printf("IN PARENT: shared mem value: *z = %d\n", *z);

  // MARK SHM FOR DESTRUCTION
  sshmdelete(shm_id);   // comment or uncomment

  // DETACH SHARED MEMORY
  sshmdt(z);
}
