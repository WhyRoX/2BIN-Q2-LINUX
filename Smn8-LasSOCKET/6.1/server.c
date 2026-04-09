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

#define MAX_PLAYERS 2
#define BACKLOG 5

typedef struct Player
{
  char pseudo[MAX_PSEUDO];
  int sockfd;
} Player;

/**** SIGNAL HANDLER ******/

volatile sig_atomic_t end = 0;

void endServerHandler(int sig)
{
  end = 1;
}

/****** FUNCTIONS ********/

/**
 * PRE:  tabPlayers: array of nbPlayers players
 * POST: print pseudos of the players in tabPlayers
 */
void displayPlayers(Player *tabPlayers, int nbPlayers)
{
  printf("\nJoueurs inscrits : \n");
  for (int i = 0; i < nbPlayers; i++)
  {
    printf("  - %s inscrit\n", tabPlayers[i].pseudo);
  }
}

/**
 * PRE:  serverPort: a valid port number
 * POST: on success, binds a socket to 0.0.0.0:serverPort and listens to it ;
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketServer(int serverPort)
{
  int sockfd = ssocket();
  sbind(SERVER_PORT, sockfd);
  slisten(sockfd, BACKLOG);
  return sockfd;
}

/****** MAIN PROGRAM ********/

int main(int argc, char **argv)
{
  StructMessage msg;
  Player tabPlayers[MAX_PLAYERS];
  int nbPlayers = 0;

  ssigaction(SIGTERM, endServerHandler);
  ssigaction(SIGINT, endServerHandler);

  int sockfd = initSocketServer(SERVER_PORT);
  printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);

  while (!end)
  {
    /* client trt */
    int newsockfd = accept(sockfd, NULL, NULL);
    if (end) break;
    checkNeg(newsockfd, "ERROR accept");

    ssize_t ret = read(newsockfd, &msg, sizeof(msg));
    if (end) break;
    checkCond(ret != sizeof(msg), "ERROR READ");

    printf("Inscription demandée par le joueur : %s\n", msg.messageText);
    if (nbPlayers < MAX_PLAYERS && strlen(msg.messageText) > 0)
    {
      msg.code = INSCRIPTION_OK;
      strcpy(tabPlayers[nbPlayers].pseudo, msg.messageText);
      tabPlayers[nbPlayers].sockfd = newsockfd;
      nbPlayers++;
    }
    else
    {
      msg.code = INSCRIPTION_KO;
    }

    nwrite(newsockfd, &msg, sizeof(msg));
    printf("Nb Inscriptions : %i\n", nbPlayers);
  }
  
  displayPlayers(tabPlayers, nbPlayers);
  x(sockfd);
}
