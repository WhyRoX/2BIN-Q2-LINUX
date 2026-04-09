/* programme où un processus crée un fils puis se met en attente de la
   fin de son fils. Le fils exécute un code qui boucle. Au bout de 3 secondes,
   le fils n'ayant pas terminé, le père tue son fils */
   
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "utils_v2.h"

//***************************************************************************//
// signal handler (pere)
//***************************************************************************//

static const char *const MSG = "Handler onalarm: je tue mon fils\n";

volatile pid_t childId;

void onalarm() {
    const size_t sz = strlen(MSG);
    write(1, MSG, sz);
    kill(childId, SIGKILL);
    _exit(10);
}

//***************************************************************************//
// MAIN
//***************************************************************************//

int main(){
    childId = sfork();
    if (childId != 0) {
        // PERE
        ssigaction(SIGALRM, onalarm);
        alarm(3);  // si mon fils n'est pas mort au bout de 3 secondes, je le tue
        swait(NULL); 
    } else {
        // FILS
        while (1) 
            printf("fils: je boucle !!!!\n");
    }
}
