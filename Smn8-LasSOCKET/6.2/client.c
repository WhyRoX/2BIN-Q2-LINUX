#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "utils.h"

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
  /* retrieve player name */
  printf("Bienvenue dans le programe de siphonage de siteweb\n");

  char url_ip[256];
  hostname_to_ip("courslinux.vinci.be", url_ip);

  int fd = sopen("sitemap.txt", O_RDONLY, 0644);
  char** table = readFileToTable(fd);
  close(fd);


  for (int i = 0; table[i] != NULL; i++) {
    char* ligne = table[i];
    
    char pageName[256];
    sprintf(pageName, "%s", strrchr(ligne, '/') + 1);
    
    int sockfd = initSocketClient(url_ip, 80);
    
    char request[512];
    sprintf(request, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", ligne, "courslinux.vinci.be");
    swrite(sockfd, request, strlen(request));

    char fileName[300];
    sprintf(fileName, "%s", pageName);

    int outfd = sopen(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    char buffer[1024];
    int bytesRead;
    while ((bytesRead = sread(sockfd, buffer, sizeof(buffer))) > 0) {
      swrite(outfd, buffer, bytesRead);
    }

    sclose(outfd);
    sclose(sockfd);
  }
}
