/*
** control_op for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:20:29 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:20:29 PM CEST botton vivien
*/

#include <unistd.h>
#include "ftpd.h"

int             send_ssl(t_client *client, void *buffer, size_t size)
{
  return (SSL_write(client->ssl, buffer, (int)size));
}

int             recv_ssl(t_client *client, void *buffer, size_t size)
{
  return (SSL_read(client->ssl, buffer, (int)size));
}

int             send_normal(t_client *client, void *buffer, size_t size)
{
  return (write(client->socket, buffer, size));
}

int		recv_normal(t_client *client, void *buffer, size_t size)
{
  return (read(client->socket, buffer, size));
}
