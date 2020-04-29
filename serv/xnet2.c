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

ssize_t		xsend(SOCKET sockfd, const void *buf, size_t len, int flags)
{
  ssize_t	res;

  res = send(sockfd, buf, len, flags);
  if (res == -1)
    perror("send");
  return (res);
}

ssize_t		xrecv(SOCKET sockfd, void *buf, size_t len, int flags)
{
  ssize_t	res;

  res = recv(sockfd, buf, len, flags);
  if (res == -1)
    perror("recv");
  return (res);
}

int		xshutdown(SOCKET sockfd, int how)
{
  int		res;

  res = shutdown(sockfd, how);
  if (res == -1)
    perror("shutdown");
  return (res);
}
