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

int main(){
    int shm_id = sshmget(SHM_KEY, sizeof(int), IPC_CREAT | PERM);
    int *n = sshmat(shm_id);

    for (int i = 0; i < 20; i++)
    {
        *n = randomIntBetween(1, 10);
        sleep(3);
    }

    sshmdt(n);
}