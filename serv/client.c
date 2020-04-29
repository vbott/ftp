/*
** client for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:20:12 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:20:12 PM CEST botton vivien
*/

#define	 _BSD_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include "ftpd.h"

static const t_code gl_code[] = {
  {331, "User name okay, need password"},
  {230, "User logged in, proceed"},
  {502, "Command not implemented"},
  {550, "Requested action not taken"},
  {250, "Requested file action okay, completed"},
  {221, "Service closing control connection"},
  {450, "Requested action not taken"},
  {200, "Command okay"},
  {150, "File status okay; about to open data connection"},
  {226, "Closing data connection"},
  {425, "Can't open data connection"},
  {426, "Connection closed; transfer aborted"},
  {451, "Requested action aborted. Local error in processing"},
  {215, "UNIX Type: L8"},
  {350, "Requested file action pending further information"},
  {500, "Syntax error, command unrecognized"},
  {220, "Service ready for new user"},
  {530, "Not logged in"},
  {501, "Syntax error in parameters or arguments"},
  {503, "Bad sequence of commands"},
  {504, "Command not implemented for that parameter"},
  {214, "\t\tUSER\tPASS\tACCT\tCWD\n\
	     CDUP\tSMNT\tQUIT\tREIN\n\
	     PORT\tPASV\tTYPE\tSTRU\n\
	     MODE\tRETR\tSTOR\tSTOU\n\
	     APPE\tALLO\tREST\tRNFR\n\
	     RNTO\tABOR\tDELE\tRMD\n\
	     MKD\tPWD\tLIST\tNLST\n\
	     SITE\tSYST\tSTAT\tHELP\n\
	     NOOP"},
  {0, NULL}
};

static void		close_client(t_client *client, t_sockfunc *sf)
{
  if (client->recv == recv_ssl)
    {
      SSL_shutdown(client->ssl);
    }
  if (client->dtp.socket != -1)
    shutdown(client->dtp.socket, SHUT_RDWR);
  if (client->dtp.file)
    fclose(client->dtp.file);
  shutdown(client->socket, SHUT_RDWR);
  close(client->epoll_fd);
  client->stop = 1;
  if (sf)
    free(sf);
  exit(EXIT_SUCCESS);
}

void			answer(int code, char *str, t_client *client)
{
  char			buffer[512];
  int			size;
  int			i;

  if (!str)
  {
    for (i = 0; gl_code[i].comment &&
		    gl_code[i].code != code; ++i);
    str = gl_code[i].comment;
  }
  size = snprintf(buffer, 512, "%d %s\r\n", code, str);
  client->send(client, buffer, size);
}

static void		init_client(t_client *client)
{
  struct epoll_event	ev;
  t_sockfunc		*tmp;

  answer(220, NULL, client);
  client->epoll_fd = epoll_create(1);
  tmp = xmalloc(sizeof(*tmp));
  tmp->in = treat_cmd;
  tmp->hangup = close_client;
  tmp->out = NULL;
  ev.events = EPOLLIN | EPOLLHUP;
  ev.data.u64 = 0;
  ev.data.ptr = tmp;
  epoll_ctl(client->epoll_fd, EPOLL_CTL_ADD, client->socket, &ev);
}

static void		loop_client(t_client *client)
{
  int           	retval;
  struct epoll_event 	events[10];
  int           	i;
  t_sockfunc		*tmp;

  init_client(client);
  while (!client->stop)
   {
     retval = epoll_wait(client->epoll_fd, events, 10, -1);
     if (retval == -1)
	exit(EXIT_FAILURE);
     for (i = 0; i < retval; i++)
     {
	tmp = (t_sockfunc*) events[i].data.ptr;
	if (events[i].events & EPOLLHUP && tmp->hangup)
	  tmp->hangup(client, tmp);
	if (events[i].events & EPOLLIN && tmp->in)
	  tmp->in(client, tmp);
	if (events[i].events & EPOLLOUT && tmp->out)
	  tmp->out(client, tmp);
     }
   }
  close_client(client, NULL);
}

void		accept_client(t_ftpd *ftpd, t_connect *connect)
{
  SOCKET	clientfd;
  t_client	*client;
  pid_t		pid;

  clientfd = xaccept(connect->socket, NULL, NULL);
  if (clientfd == INVALID_SOCKET)
    return ;
  client = xmalloc(sizeof(*client));
  if (!client)
    return ;
  memset(client, 0, sizeof(*client));
  client->recv = recv_normal;
  client->send = send_normal;
  client->root = getcwd(NULL, 0);
  client->socket = clientfd;
  client->ssl = SSL_new(ftpd->ctx);
  client->ctx = ftpd->ctx;
  client->addr = ftpd->addr;
  client->dtp.active = -1;
  client->dtp.recv = recv_normal_dtp;
  client->dtp.send = send_normal_dtp;
  if ((pid = fork()) != -1 && pid == 0)
    loop_client(client);
  free(client);
}
