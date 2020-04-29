/*
** init for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:31 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:31 PM CEST botton vivien
*/

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <signal.h>
#include <fcntl.h>
#include "ftpd.h"

static void		init_ssl(t_ftpd *ftpd)
{
  SSL_load_error_strings();
  SSL_library_init();
  ftpd->ctx = SSL_CTX_new(SSLv23_server_method());
  SSL_CTX_use_certificate_file(ftpd->ctx, "keyfile.pem", SSL_FILETYPE_PEM);
  SSL_CTX_use_PrivateKey_file(ftpd->ctx, "keyfile.pem", SSL_FILETYPE_PEM);
  SSL_CTX_set_options(ftpd->ctx, SSL_OP_ALL);
}

void			init(t_ftpd *ftpd, struct addrinfo *hints,
					char *addr, int ipversion)
{
  struct sigaction      act;

  memset(&act, 0, sizeof(act));
  memset(ftpd, 0, sizeof(*ftpd));
  init_ssl(ftpd);
  act.sa_handler = SIG_DFL;
  act.sa_flags = SA_NOCLDWAIT;
  sigemptyset(&act.sa_mask);
  sigaddset(&act.sa_mask, SIGPIPE);
  sigaction(SIGCHLD, &act, NULL);
  memset(hints, 0, sizeof(*hints));
  hints->ai_family = ipversion;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_protocol = IPPROTO_TCP;
  hints->ai_flags = AI_PASSIVE;
  ftpd->epoll_fd = epoll_create(1);
  ftpd->addr = addr;
}

static void	fill_ftpd(t_ftpd *ftpd, SOCKET tmp)
{
  t_connect     *temp;
  struct epoll_event ev;

  temp = xmalloc(sizeof(*temp));
  temp->socket = tmp;
  temp->next =  ftpd->connects;
  ftpd->connects = temp;
  ev.events = EPOLLIN;
  ev.data.u64 = 0;
  ev.data.ptr = temp;
  epoll_ctl(ftpd->epoll_fd, EPOLL_CTL_ADD, tmp, &ev);
}

int		listen_to_port(t_ftpd *ftpd, char *port,
				struct addrinfo *hints)
{
  t_addrinfo	*cpy;
  t_addrinfo	*result;
  SOCKET	tmp;

  if (getaddrinfo(NULL, port, hints, &result) != 0)
    return (-1);
  for (cpy = result; cpy; cpy = cpy->ai_next)
    {
     tmp = xsocket(cpy->ai_family, cpy->ai_socktype, cpy->ai_protocol);
     if (tmp == INVALID_SOCKET)
      continue ;
     if (xbind(tmp, cpy->ai_addr, cpy->ai_addrlen) == 0
		     && xlisten(tmp, 5) == 0)
      fill_ftpd(ftpd, tmp);
    }
  freeaddrinfo(result);
  return (0);
}
