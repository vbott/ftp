/*
** xnet.h for raytracer in /home/snap/projects/raytracer/clustering
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Wed May 26 13:51:40 2010 botton vivien
** Last update Tue Jun  1 14:44:28 2010 botton vivien
*/

#ifndef		_XNET_H_
# define	_XNET_H_

# if defined (WIN32)
#  include <winsock2.h>
#  include <ws2tcpip.h>
# else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <netdb.h>
# endif

#define _POSIX_C_SOURCE 1

# ifndef	SOCKET
#  define	SOCKET int
# endif		/* !SOCKET */

# ifndef	INVALID_SOCKET
#  define	INVALID_SOCKET -1
# endif		/* !INVALID_SOCKET*/

# ifndef	SOCKET_ERROR
#  define	SOCKET_ERROR -1
# endif		/* !SOCKET_ERROR*/

# ifndef	SHUT_RD
#  define	SHUT_RD SD_RECEIVE
# endif		/* !SHUT_RD*/

# ifndef	SHUT_WR
#  define	SHUT_WR SD_SEND
# endif		/* !SHUT_WR */

# if	!defined (__socklen_t_defined) && !defined (_SOCKLEN_T_DECLARED)
typedef int	socklen_t;
# endif		/* !__socklen_t_defined && _SOCKLEN_T_DECLARED */

typedef unsigned char uchar;
typedef struct addrinfo t_addrinfo;

typedef struct s_socket
{
  struct sockaddr_in6 info;
  int		sockfd;
  char	        server;
}		t_socket;

typedef struct s_packet
{
  char		channel;
  int		length;
  uchar		*data;
}		t_packet;

SOCKET	xsocket(int domain, int type, int protocol);
int	xbind(SOCKET sockfd, const struct sockaddr *addr, socklen_t addrlen);
int	xlisten(SOCKET sockfd, int backlog);
SOCKET	xaccept(SOCKET sockfd, struct sockaddr *addr, socklen_t *addrlen);
int	xconnect(SOCKET sockfd, const struct sockaddr *addr,
		 socklen_t addrlen);
int	xshutdown(SOCKET sockfd, int how);
ssize_t xsend(int sockfd, const void *buf, size_t len, int flags);
ssize_t xrecv(int sockfd, void *buf, size_t len, int flags);

#endif		/* !_XNET_H */
