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

    for (int i = 0; i < 12; i++)
    {
        *n = randomIntBetween(1, 100);
        printf("%d: the distance? is : %d\n", i, *n);
        sleep(5);
    }

    sshmdt(n);
    sshmdelete(shm_id);
}