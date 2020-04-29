/*
** main for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:42 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:42 PM CEST botton vivien
*/

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include "ftpd.h"

static void	waiting_clients(t_ftpd *ftpd)
{
  int		retval;
  struct epoll_event events[10];
  int		i;

  while (1)
    {
      retval = epoll_wait(ftpd->epoll_fd, events, 10, -1);
      if (retval == -1 && errno != EINTR)
	exit(EXIT_FAILURE);
      for (i = 0; i < retval; i++)
	accept_client(ftpd, (t_connect*) events[i].data.ptr);
    }
}

static char	*replace(char *str)
{
  int		i;

  for (i = 0; str[i]; i++)
   {
     if (str[i] == '.')
	str[i] = ',';
   }
  return (str);
}

int		main(int ac, char **av)
{
  t_ftpd	ftpd;
  t_addrinfo	hints;
  t_connect     *temp;
  char		*addr;

  if (ac < 2)
  {
    fprintf(stderr, "usage : ./ftpd port [addr]\n");
    return (EXIT_FAILURE);
  }
  addr = (ac >= 3) ? replace(av[2]) : "127,0,0,1";
  init(&ftpd, &hints, addr, IPV4_ONLY);
  temp = ftpd.connects;
  if (listen_to_port(&ftpd, av[1], &hints) == -1
	|| temp == ftpd.connects)
      return (EXIT_FAILURE);
  waiting_clients(&ftpd);
  return (EXIT_SUCCESS);
}
