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
#include "client.h"

int             send_normal(t_client *client, void *buffer, size_t size)
{
  return (write(client->ctl_socket, buffer, size));
}

int		recv_normal(t_client *client, void *buffer, size_t size)
{
  return (read(client->ctl_socket, buffer, size));
}

int             send_dtp(t_client *client, void *buffer, size_t size)
{
  return (write(client->dtp_socket, buffer, size));
}

int		recv_dtp(t_client *client, void *buffer, size_t size)
{
  return (read(client->dtp_socket, buffer, size));
}
