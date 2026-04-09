#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "utils_v2.h"

#define SHM_KEY 250  // Conseil: utilisez 'echo $RANDOM' pour générer vos clés
#define SEM_KEY 370
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
    if (accounts[1]%100 == 0) {
        accounts[0]+=50;
        usleep(1);
        accounts[1]-=50;
    } else {
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
    printf("IN PARENT: Bank accounts statement = [%2d,%4d] sum = %d\n", \
                 accounts[0], accounts[1], accounts[0]+accounts[1]);
    // END OF CRITICAL SECTION
    sem_up0(sem_id);
  }

  sshmdt(accounts);

  swaitpid(cpid, NULL, 0); // make sure child finishes before removing semaphores

  // COMMENT OR UNCOMMENT
  sshmdelete(shm_id);
  sem_delete(sem_id);
}
