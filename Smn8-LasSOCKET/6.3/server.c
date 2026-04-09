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

#define BACKLOG 5
#define MAX_MSG 256

/**** SIGNAL HANDLER ******/

volatile sig_atomic_t end = 0;

void endServerHandler(int sig)
{
  end = 1;
}

/****** FUNCTIONS ********/

/**
 * PRE:  serverPort: a valid port number
 * POST: on success, binds a socket to 0.0.0.0:serverPort and listens to it ;
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketServer(int serverPort)
{
  int sockfd = ssocket();
  sbind(serverPort, sockfd);
  slisten(sockfd, BACKLOG);
  return sockfd;
}

/****** MAIN PROGRAM ********/

int main(int argc, char **argv)
{
  char request[MAX_MSG + 1];
  char response[MAX_MSG + 1];

  ssigaction(SIGTERM, endServerHandler);
  ssigaction(SIGINT, endServerHandler);

  int sockfd = initSocketServer(SERVER_PORT);
  printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);

  while (!end)
  {
    int newsockfd = accept(sockfd, NULL, NULL);
    if (end) break;
    checkNeg(newsockfd, "ERROR accept");

    int ret = sread(newsockfd, request, sizeof(request));
    checkCond(ret <= 0, "ERROR READ");
    
    if (ret >= (int)sizeof(request)) {
      ret = sizeof(request) - 1;
    }
    request[ret] = '\0';
    int messageLength = strlen(request);
    printf("Message reçu : %s\n", request);

    snprintf(response, sizeof(response), "ACK %zu %s", messageLength, getTime());
    nwrite(newsockfd, response, sizeof(response));
    sclose(newsockfd);
  }

  sclose(sockfd);
}
