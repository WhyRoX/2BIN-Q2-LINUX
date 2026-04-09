#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "utils.h"

#define SHM_KEY 26418 // Conseil: utilisez 'echo $RANDOM' pour générer vos clés
#define SEM_KEY 15990
#define PERM 0666

//******************************************************************************//
// CHILD HANDLER
//******************************************************************************//
void child_handler()
{
    // GET SEMAPHORE
    int sem_id = sem_get(SEM_KEY, 1);

    for (int i = 0; i < 3; i++)
    {
        sem_down0(sem_id);
        printf("je suis le fils %d\n", getpid());
        sleep(1);
        sem_up0(sem_id);
    }
    
  
}

//******************************************************************************//
// MAIN FUNCTION
//******************************************************************************//
int main(int argc, char *argv[])
{
    // CREATE SEMAPHORE
    int sem_id = sem_create(SEM_KEY, 1, PERM, 1);

    pid_t cpid1 = fork_and_run0(child_handler);
    pid_t cpid2 = fork_and_run0(child_handler);

    swaitpid(cpid1, NULL, 0);
    swaitpid(cpid2, NULL, 0);



  // MARK SHM FOR DESTRUCTION
  sem_delete(sem_id);   // comment or uncomment
}
