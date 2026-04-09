#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "messages.h"
#include "utils_v2.h"


char* ip;

/**
 * PRE: serverIP : a valid IP address
 *      serverPort: a valid port number
 * POST: on success, connects a client socket to serverIP:serverPort
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketClient(char *serverIP, int serverPort)
{
  int sockfd = ssocket();

  // prepare socket to connect
  sconnect(serverIP, serverPort, sockfd);
  return sockfd;
}


int main(int argc, char **argv)
{
  /* retrieve player name */
  printf("Bienvenue dans le programe de dl page web\n");
  printf("Entrez l'url :\n");
  StructMessage ip;
  int line = sread(0, ip.url_ip, MAX_URL);
  if (line < 2)
  {
    printf("Erreur: vous devez entrer url\n");
    exit(1);
  }
  hostname_to_ip(ip.url_ip, ip.url_ip);

  int sockfd = initSocketClient(ip, SERVER_PORT);
  
  char** page = readFileToTable(sockfd);

  sprintf(page,"%s",strrchr(line,'/')+1);

  sclose(sockfd);
  return 0;
}
