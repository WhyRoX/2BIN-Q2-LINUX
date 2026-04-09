#include <unistd.h>
#include "utils_v2.h"

int main(int argc, char **argv) {
   int pipefd[2];
   spipe(pipefd);
      
   pid_t child1 = sfork();
   if (child1 != 0) {
       
       pid_t child2 = sfork();
       if (child2 != 0) {
           // PERE
           sclose(pipefd[0]);
           sclose(pipefd[1]);
           
           swait(NULL);
           swait(NULL);
       } else {
           // FILS 2
           sclose(pipefd[1]);

           sdup2(pipefd[0], 0);
   
           execvp(argv[2], &argv[2]);
           perror("Exec 2 failed");           
       }
   } else {
       // FILS 1       
       sclose(pipefd[0]);

       sdup2(pipefd[1], 1);
   
       execlp(argv[1], argv[1], NULL);
       perror("Exec 1 failed");
   }
}


/*

man exec : extraits

   int execlp(const char *file, const char *arg, ..., (char*) NULL);
   --> file=nom du fichier à exécuter (recherche de l'exécutable dans PATH) ; 
       arg0=file ; argi=liste des arguments terminée par NULL
   
   int execvp(const char *file, char *const argv[]);
   --> file=nom du fichier à exécuter (recherche de l'exécutable dans PATH) ; 
       argv=tableau représentant la ligne de commande (où argv[0]=file)


   Extraits de man exec:
   
   l - execl(), execlp(), execle()
       The  const  char *arg  and subsequent ellipses can be thought of as arg0, arg1, ..., argn.  Together they
       describe a list of one or more pointers to null-terminated  strings  that  represent  the  argument  list
       available to the executed program.  The first argument, by convention, should point to the filename asso‐
       ciated with the file being executed.

   v - execv(), execvp(), execvpe()
       The char *const argv[] argument is an array of pointers to null-terminated strings that represent the ar‐
       gument  list  available to the new program.  The first argument, by convention, should point to the file‐
       name associated with the file being executed.  The array  of  pointers  must  be  terminated  by  a  null
       pointer.

   p - execlp(), execvp(), execvpe()
       These  functions  duplicate the actions of the shell in searching for an executable file if the specified
       filename does not contain a slash (/) character.  The file is sought in the colon-separated list  of  di‐
       rectory  pathnames  specified in the PATH environment variable.

 */
