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
#include "utils.h"

#define MAX_MSG 256

/****** FUNCTIONS ********/

/**
 * PRE: serverIP: a valid IP address
 *      serverPort: a valid port number
 * POST: on success, connects a client socket to serverIP:serverPort
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketClient(char * serverIP, int serverPort)
{
  int sockfd = ssocket();
  sconnect(serverIP, serverPort, sockfd);
  return sockfd;
}

/****** MAIN PROGRAM ********/

int main(int argc, char **argv)
{
  printf("Entrez un message :\n");

  char message[MAX_MSG + 1] = {0};
  int ret = readLimitedLine(message, MAX_MSG + 2);
  if (ret < 0)
  {
    printf("Erreur: impossible de lire le message\n");
    exit(1);
  }

  int sockfd = initSocketClient(SERVER_IP, SERVER_PORT);
  nwrite(sockfd, message, sizeof(message));

  char response[MAX_MSG + 1] = {0};
  int readRet = sread(sockfd, response, sizeof(response));
  checkCond(readRet <= 0, "ERROR READ");
  response[MAX_MSG] = '\0';

  printf("%s\n", response);

  sclose(sockfd);
}
