/*
** utils for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:18:12 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:18:12 PM CEST botton vivien
*/

#define _XOPEN_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include "net.h"

int		connect_to(char *addr, char *port)
{
  t_addrinfo	*cpy;
  t_addrinfo	*result;
  t_addrinfo	hints;
  SOCKET	tmp;

  tmp = -1;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  if (getaddrinfo(addr, port, &hints, &result) != 0)
    return (-1);
  for (cpy = result; cpy; cpy = cpy->ai_next)
    {
     tmp = xsocket(cpy->ai_family, cpy->ai_socktype, cpy->ai_protocol);
     if (tmp == INVALID_SOCKET)
      continue ;
     if (xconnect(tmp, cpy->ai_addr, cpy->ai_addrlen) == 0)
      break ;
    }
  freeaddrinfo(result);
  return (tmp);
}

int		listen_to(char *port)
{
  t_addrinfo	*cpy;
  t_addrinfo	*result;
  t_addrinfo	hints;
  SOCKET	tmp;

  tmp = -1;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(NULL, port, &hints, &result) != 0)
    return (-1);
  for (cpy = result; cpy; cpy = cpy->ai_next)
    {
     tmp = xsocket(cpy->ai_family, cpy->ai_socktype, cpy->ai_protocol);
     if (tmp == INVALID_SOCKET)
      continue ;
     if (xbind(tmp, cpy->ai_addr, cpy->ai_addrlen) == 0
		     && xlisten(tmp, 5) == 0)
      break ;
    }
  freeaddrinfo(result);
  return (tmp);
}
