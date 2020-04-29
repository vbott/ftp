/*
** dtp_op for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:02 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:02 PM CEST botton vivien
*/

#include <unistd.h>
#include "ftpd.h"

int             send_ssl_dtp(t_dtp *dtp, void *buffer, size_t size)
{
  return (SSL_write(dtp->ssl, buffer, (int)size));
}

int             recv_ssl_dtp(t_dtp *dtp, void *buffer, size_t size)
{
  return (SSL_read(dtp->ssl, buffer, (int)size));
}

int             send_normal_dtp(t_dtp *dtp, void *buffer, size_t size)
{
  return (write(dtp->socket, buffer, size));
}

int		recv_normal_dtp(t_dtp *dtp, void *buffer, size_t size)
{
  return (read(dtp->socket, buffer, size));
}
