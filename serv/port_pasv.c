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
#include <sys/epoll.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include "ftpd.h"

void	     remove_fd(t_client *client)
{
  if (client->dtp.socket != -1)
  {
    epoll_ctl(client->epoll_fd, EPOLL_CTL_DEL, client->dtp.socket, NULL);
    if (client->recv == recv_ssl)
      SSL_shutdown(client->ssl);
    close(client->dtp.socket);
    client->dtp.socket = -1;
  }
}

int          port(char *arg, t_client *client)
{
  char	     ip[256];
  char	     *str;
  int	     addr[6];
  int	     i;
  char	     port[8];

  i = 0;
  for (str = strtok(arg, ","); str && i < 6; str = strtok(NULL, ","))
   {
     if (strlen(str) > 3)
	return (501);
     addr[i] = strtol(str, NULL, 10);
     i++;
   }
  if (i == 6 && str)
   return (501);
  snprintf(ip, 256, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
  snprintf(port, 8, "%d", (addr[4] << 8) + addr[5]);
  remove_fd(client);
  client->dtp.socket = connect_to(ip, port);
  client->dtp.active = 1;
  return (200);
}

static void	     	accept_pasv(t_client *client, t_sockfunc *sf)
{
  int	     fd;

  fd = accept(client->dtp.accept_socket, NULL, NULL);
  if (fd != -1)
  {
   free(sf);
   epoll_ctl(client->epoll_fd, EPOLL_CTL_DEL, client->dtp.accept_socket, NULL);
   close(client->dtp.accept_socket);
   client->dtp.socket = fd;
   if (client->recv == recv_ssl)
    {
	client->dtp.ssl = SSL_new(client->ctx);
    	SSL_set_fd(client->dtp.ssl, client->dtp.socket);
	if (SSL_accept(client->dtp.ssl) != 1)
	  {
	    shutdown(client->dtp.socket, SHUT_RDWR);
	    client->dtp.socket = -1;
	  }
	else
	 {
	   client->dtp.recv = recv_ssl_dtp;
	   client->dtp.send = send_ssl_dtp;
	 }
    }
  }
}

static void		add_pasv(int port, t_client *client)
{
  struct epoll_event    ev;
  t_sockfunc            *tmp;
  char                  buffer[256];

  tmp = xmalloc(sizeof(*tmp));
  tmp->in = accept_pasv;
  tmp->hangup = NULL;
  tmp->out = NULL;
  ev.events = EPOLLIN;
  ev.data.ptr = tmp;
  epoll_ctl(client->epoll_fd, EPOLL_CTL_ADD, client->dtp.accept_socket, &ev);
  snprintf(buffer, 256, "Entering Passive Mode (%s,%d,%d)", client->addr,
		  port >> 8, port - ((port >> 8) << 8));
  answer(227, buffer, client);
}

int			pasv(char *arg, t_client *client)
{
  char			port_str[12];
  static		int port = 45000;

  (void)(arg);
  remove_fd(client);
  client->dtp.active = 0;
  do
  {
    snprintf(port_str, 12, "%d", port);
    client->dtp.accept_socket = listen_to(port_str);
    port++;
  }
  while (client->dtp.accept_socket == -1 && port < 45050);
  if (port >= 45050)
   {
    port = 45001;
    answer(550, NULL, client);
   }
  else
     add_pasv(port - 1, client);
  return (0);
}
