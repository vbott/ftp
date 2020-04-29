/*
** auth for fptd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:19:43 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:19:43 PM CEST botton vivien
*/

#define  _BSD_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "ftpd.h"

int	     auth(char *arg, t_client *client)
{
  if (strcmp(arg, "SSL"))
    return (504);
  answer(200, NULL, client);
  SSL_set_fd(client->ssl, client->socket);
  if (SSL_accept(client->ssl) != 1)
    return (550);
  else
    {
      client->recv = recv_ssl;
      client->send = send_ssl;
    }
  return (0);
}

int          user(char *arg, t_client *client)
{
  if (client->user)
    free(client->user);
  client->user = strdup(arg);
  return (331);
}

int          pass(char *arg, t_client *client)
{
  if (client->user)
    free(client->user);
  client->user = NULL;
  client->authenticated = 1;
  (void)(arg);
  return (230);
}

int          account(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}
