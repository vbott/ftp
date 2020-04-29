/*
** port_pasv for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:52 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:52 PM CEST botton vivien
*/

#define	 _BSD_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include "client.h"

static int		recv_response_buff(t_client *client, char *buffer)
{
  int			readed;

  readed = client->recv(client, buffer, 4095);
  if (readed == 0 || readed == -1)
  {
    fprintf(stdout, "Disconnected\n");
    exit(EXIT_SUCCESS);
  }
  write(1, buffer, readed);
  buffer[readed] = '\0';
  return (strtol(buffer, NULL, 10));
}

void          passive(t_client *client)
{
  char	     ip[256];
  char	     *str;
  int	     addr[6];
  int	     i;
  char	     port[8];
  char	     buffer[4096];
  char	     *arg;

  i = 0;
  send_cmd("PASV", NULL, client);
  recv_response_buff(client, buffer);
  arg = strtok(buffer, "(");
  arg = strtok(NULL, "(");
  if (!arg)
    return ;
  for (str = strtok(arg, ","); str && i < 6; str = strtok(NULL, ","))
     addr[i++] = strtol(str, NULL, 10);
  if (i == 6 && str)
   return ;
  snprintf(ip, 256, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
  snprintf(port, 8, "%d", (addr[4] << 8) + addr[5]);
  remove_fd(client);
  client->dtp_socket = connect_to(ip, port);
}

static void		do_loop(fd_set *set, int *i, t_client *client)
{
  struct timeval	tv;
  int			socket;
  fd_set		tmp;

  tv.tv_sec = 1;
  tv.tv_usec = 0;
  memcpy(&tmp, set, sizeof(tmp));
  if (select(client->dtp_socket + 1, &tmp, NULL, NULL, &tv) == -1)
     return ;
  else if (FD_ISSET(client->dtp_socket, &tmp))
   {
       socket = accept(client->dtp_socket, NULL, NULL);
       close(client->dtp_socket);
       client->dtp_socket = socket;
       recv_response(client);
       *i = 20000;
   }
}

static void		add_pasv(int port, t_client *client)
{
  char                  buffer[256];
  fd_set		set;
  int			i;

  FD_ZERO(&set);
  FD_SET(client->dtp_socket, &set);
  i = 0;
  snprintf(buffer, 256, "127,0,0,1,%d,%d", port >> 8, port
		  - ((port >> 8) << 8));
  send_cmd("PORT", buffer, client);
  while (i < 3)
   {
     do_loop(&set, &i, client);
     i++;
   }
  if (i != 20001)
    remove_fd(client);
}

void			active(t_client *client)
{
  char			port_str[12];
  static		int port = 20000;

  remove_fd(client);
  do
  {
    snprintf(port_str, 12, "%d", port);
    client->dtp_socket = listen_to(port_str);
    port++;
  }
  while (client->dtp_socket == -1 && port < 45000);
  if (port >= 45000)
    port = 20000;
  else
     add_pasv(port - 1, client);
}
