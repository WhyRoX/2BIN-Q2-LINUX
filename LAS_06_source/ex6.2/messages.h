#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#define SERVER_PORT 80     // Utilisez un port de votre fichier ~/LAS_assigned_ports.txt
#define SERVER_IP "127.0.0.1" /* localhost */
#define MAX_URL 256

/* struct message used between server and client */
typedef struct
{
  char url_ip[MAX_URL];
} StructMessage;

#endif
