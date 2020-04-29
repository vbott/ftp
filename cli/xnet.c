/*
** xnet.c for raytracer in /home/snap/projects/raytracer/clustering
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Wed May 26 13:55:36 2010 botton vivien
** Last update Sun Jun  6 23:02:20 2010 botton vivien
*/

#include <stdio.h>
#include "net.h"

SOCKET		xsocket(int domain, int type, int protocol)
{
  SOCKET	res;

  res = socket(domain, type, protocol);
  if (res == -1)
    perror("socket");
  return (res);
}

int		xbind(SOCKET sockfd, const struct sockaddr *addr,
		      socklen_t addrlen)
{
  int		res;

  res = bind(sockfd, addr, addrlen);
  if (res == -1)
    perror("bind");
  return (res);
}

int		xlisten(SOCKET sockfd, int backlog)
{
  int		res;

  res = listen(sockfd, backlog);
  if (res == -1)
    perror("listen");
  return (res);
}

SOCKET		xaccept(SOCKET sockfd, struct sockaddr *addr,
			socklen_t *addrlen)
{
  int		res;

  res = accept(sockfd, addr, addrlen);
  if (res == -1)
    perror("accept");
  return (res);
}

int	xconnect(SOCKET sockfd, const struct sockaddr *addr,
	    socklen_t addrlen)
{
  int	res;

  res = connect(sockfd, addr, addrlen);
  if (res == -1)
    perror("connect");
  return (res);
}

