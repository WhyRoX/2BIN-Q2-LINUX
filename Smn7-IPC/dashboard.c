#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "utils_v2.h"

#define SHM_KEY 29950 // Conseil: utilisez 'echo $RANDOM' pour générer vos clés
#define SEM_KEY 443
#define PERM 0666

#define NBR_LOOPS 12

//******************************************************************************//
// MAIN FUNCTION
//******************************************************************************//
int main(int argc, char *argv[])
{
    // CREATE SEMAPHORE
    // int sem_id = sem_create(SEM_KEY, 1, PERM, 1);

    // CREATE SHARED MEMORY
    int shm_id = sshmget(SHM_KEY, 2 * sizeof(int), IPC_CREAT | PERM);
    int *z = sshmat(shm_id);

    for (int i = 0; i < NBR_LOOPS; i++)
    {
        // sem_down0(sem_id);

        *z = randomIntBetween(1, 100);
        printf("[%d] The speed is : %d \n", i, *z);
        sleep(1);
        // sem_up0(sem_id);
    }

    sshmdt(z);
}