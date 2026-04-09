/* Accès à une shm contenant 2 entiers, partagée entre 
   un processus père et son fils, et protégée par un
   sémaphore. Le père a la responsabilité de créer les IPCs
   (avant fork) et de les détruire.
   Utilisation des fonctions shm et sem du module utils. */
   
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "utils.h"

#define SHM_KEY 250
#define SEM_KEY 214
#define PERM 0666

#define BANK_VALUE 1000
#define NBR_LOOPS 500

//******************************************************************************//
// CHILD HANDLER
//******************************************************************************//

void child_handler()
{
  // GET SEMAPHORE
  int sem_id = sem_get(SEM_KEY, 1);
  // GET SHARED MEMORY
  int shm_id = sshmget(SHM_KEY, 2*sizeof(int), 0);
  int *accounts = sshmat(shm_id);

  for (int i = 0; i != NBR_LOOPS; i++)
  {
    sem_down0(sem_id);
    // START OF CRITICAL SECTION
    if (accounts[1]%100 == 0) {  // transfert du compte 1 vers le compte 0
        accounts[0]+=50;
        usleep(1);
        accounts[1]-=50;
    } else {                  // transfert du compte 0 vers le compte 1
        accounts[0]-=50;
        usleep(1);
        accounts[1]+=50;
    }
    // END OF CRITICAL SECTION
    sem_up0(sem_id);
  }
  sshmdt(accounts);
}

//******************************************************************************//
// MAIN FUNCTION
//******************************************************************************//

int main(int argc, char *argv[])
{
  // CREATE SEMAPHORE
  int sem_id = sem_create(SEM_KEY, 1, PERM, 1); // init semaphores before fork to avoid race conditions
  // CREATE SHARED MEMORY
  int shm_id = sshmget(SHM_KEY, 2*sizeof(int), IPC_CREAT | PERM);
  int* accounts = sshmat(shm_id);
  accounts[0] = 0;  // inutile
  accounts[1] = BANK_VALUE;

  pid_t cpid = fork_and_run0(child_handler);

  for (int i = 0; i != NBR_LOOPS; i++)
  {
    sem_down0(sem_id);
    // START OF CRITICAL SECTION
        printf("IN PARENT: Bank accounts statement = [%2d,%4d] sum =\033[0;33m %d \033[0m(should always be %d)\n", \
                 accounts[0], accounts[1], accounts[0]+accounts[1], BANK_VALUE);
    // END OF CRITICAL SECTION
    sem_up0(sem_id);
  }

  swaitpid(cpid, NULL, 0); // make sure child finishes before removing semaphores!

  // DESTRUCTION OF IPCs
  sshmdelete(shm_id);   // comment or uncomment
  sem_delete(sem_id);   // comment or uncomment
  
  sshmdt(accounts);
}
