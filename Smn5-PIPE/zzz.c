#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "utils_v2.h"

#define BUFFERSIZE 80
#define MSG_SIZE 30

void run_child (void* arg1, void* arg2)
{
   // PROCESSUS FILS
   int* pipePF = arg1;
   int* pipeFP = arg2;

   // Cloture du descripteur d'écriture
   sclose(pipePF[1]);
   sclose(pipeFP[0]);

   // Boucle de lecture sur le pipe, somme des valeurs lues
   // et écriture du résultat au père
   int nbChar, val;
   int sum = 0, count = 0;
   while (sread(pipePF[0], &val, sizeof(int))) {
      count++;
      sum += val;
      nwrite(pipeFP[1], &sum, sizeof(int));
   }
   
   // Ecriture de la moyenne au père
   double average = (double) sum / count;
   nwrite(pipeFP[1], &average, sizeof(double));

   // Cloture du descripteur de lecture
   sclose(pipePF[0]);
   sclose(pipeFP[1]);
}

int main(int argc, char **argv)
{
   // Création des pipes
   int pipePF[2];
   spipe(pipePF);
   int pipeFP[2];
   spipe(pipeFP);
   
   // Création de l'enfant
   fork_and_run2(run_child, pipePF, pipeFP);

   // PROCESSUS PARENT
   // Cloture des descripteur non utilisés
   sclose(pipePF[0]);
   sclose(pipeFP[1]);

   // Boucle de lecture au clavier, écriture sur pipe au fils,
   // lecture du résultat sur pipe et affichage à l'écran
   printf("Enter integers, one per line (Ctrl-D to finish):\n");
   int val, sum;
   while (scanf("%d",&val) != EOF) {
      nwrite(pipePF[1], &val, sizeof(int));
      sread(pipeFP[0], &sum, sizeof(int));
      
      // affichage avec printf:
      //printf("sum = %d\n", sum);
      // affichage avec write:
      char msg[MSG_SIZE];
      sprintf(msg, "sum = %d\n", sum);
      nwrite(1,msg,strlen(msg));
   }

   // Cloture du descripteur d'écriture au fils --> provoque la fin du fils
   sclose(pipePF[1]);

   // Lecture du compteur de valeurs envoyé par le fils
   double res;
   sread(pipeFP[0], &res, sizeof(double));
   
   // affichage avec printf:
   //printf("\n--> average = %.3f\n", res);
   // affichage avec write:
   char msg[MSG_SIZE];
   sprintf(msg, "\n--> average = %.3f\n", res);
   nwrite(1,msg,strlen(msg));

   // Cloture des descripteurs ouverts
   sclose(pipeFP[0]);
}
