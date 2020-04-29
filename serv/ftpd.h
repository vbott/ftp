/*
** xnet.h for raytracer in /home/snap/projects/raytracer/clustering
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Wed May 26 13:51:40 2010 botton vivien
** Last update Tue Jun  1 14:44:28 2010 botton vivien
*/

#ifndef		_FTPD_H_
# define	_FTPD_H_

#include <openssl/ssl.h>
#include <stdio.h>
#include "net.h"

# define TRUE 1
# define FALSE 0

# define IPV4_ONLY  AF_INET
# define IPV6_ONLY  AF_INET6
# define IP_MIXED AF_UNSPEC

# define PACKET_LEN 4096

typedef	struct 	s_dtp
{
  int		active;
  FILE		*file;
  int		bit_pos;
  int		socket;
  int		accept_socket;
  SSL           *ssl;
  int           (*recv)(struct s_dtp*, void*, size_t);
  int           (*send)(struct s_dtp*, void*, size_t);
} 		t_dtp;

typedef struct s_client
{
  t_dtp		dtp;
  char		*root;
  char		*addr;
  int		epoll_fd;
  int		socket;
  SSL		*ssl;
  SSL_CTX	*ctx;
  int		authenticated;
  int		stop;
  char		*user;
  char          *data;
  int		(*recv)(struct s_client*, void*, size_t);
  int           (*send)(struct s_client*, void*, size_t);
}		t_client;

typedef struct	s_sockfunc
{
  void		(*in)(t_client *, struct s_sockfunc*);
  void          (*out)(t_client *, struct s_sockfunc*);
  void		(*hangup)(t_client *, struct s_sockfunc*);
} 		t_sockfunc;

typedef struct s_connect
{
  int		socket;
  struct s_connect *next;
}		t_connect;

typedef struct s_ftpd
{
  int		epoll_fd;
  char		*addr;
  SSL_CTX	*ctx;
  t_connect	*connects;
  size_t	nb_clients;
}		t_ftpd;

typedef struct	s_cmd
{
  char          *cmd;
  int		nb_args;
  int		mandatory;
  int		authenticated;
  struct s_cmd const 	*prev;
  int          (*func)(char *arg, t_client*);
}		t_cmd;

typedef	struct	s_code
{
  int		code;
  char		*comment;
}		t_code;

/* control_op.c */
int             send_ssl(t_client *client, void *buffer, size_t size);
int             send_normal(t_client *client, void *buffer, size_t size);
int             recv_ssl(t_client *client, void *buffer, size_t size);
int             recv_normal(t_client *client, void *buffer, size_t size);

/* dtp_op.c */
int             send_ssl_dtp(t_dtp *, void *buffer, size_t size);
int             send_normal_dtp(t_dtp *,
	       	void *buffer, size_t size);
int             recv_ssl_dtp(t_dtp *, void *buffer, size_t size);
int             recv_normal_dtp(t_dtp *,
	       	void *buffer, size_t size);

/* cmd.c */
void			treat_cmd(t_client *client, t_sockfunc *sf);

/* init.c */
void		init(t_ftpd *ftpd, t_addrinfo *hints, char *, int ipversion);
int		listen_to_port(t_ftpd *ftpd, char *port,
				t_addrinfo *hints);

/* utils.c */
int             connect_to(char *addr, char *port);
int             listen_to(char *port);

/* client.c */
void		accept_client(t_ftpd *ftp, t_connect *connect);
void		answer(int, char*, t_client*);

/* port_pasv.c */
void         	remove_fd(t_client *client);

/* file_op */
void		hangup_file(t_client *, t_sockfunc *sf);
void            recv_file(t_client *, t_sockfunc *sf);
void            send_file(t_client *, t_sockfunc *sf);

/* xfunctions.c */
void		*xmalloc(size_t);

/* functions */
  int	       auth(char *arg, t_client*);
  int          user(char *arg, t_client*);
  int          pass(char *arg, t_client*);
  int          account(char *arg, t_client*);
  int          cwd(char *arg, t_client*);
  int          cdup(char *arg, t_client*);
  int          smnt(char *arg, t_client*);
  int          quit(char *arg, t_client*);
  int          rein(char *arg, t_client*);
  int          port(char *arg, t_client*);
  int          pasv(char *arg, t_client*);
  int          type(char *arg, t_client*);
  int          stru(char *arg, t_client*);
  int          mode(char *arg, t_client*);
  int          retr(char *arg, t_client*);
  int          stor(char *arg, t_client*);
  int          stou(char *arg, t_client*);
  int          appe(char *arg, t_client*);
  int          allo(char *arg, t_client*);
  int          rest(char *arg, t_client*);
  int          rnfr(char *arg, t_client*);
  int          rnto(char *arg, t_client*);
  int          abor(char *arg, t_client*);
  int          dele(char *arg, t_client*);
  int          rmd(char *arg, t_client*);
  int          mkd(char *arg, t_client*);
  int          pwd(char *arg, t_client*);
  int          list(char *arg, t_client*);
  int          nlst(char *arg, t_client*);
  int          site(char *arg, t_client*);
  int          syst(char *arg, t_client*);
  int          status(char *arg, t_client*);
  int          help(char *arg, t_client*);
  int          noop(char *arg, t_client*);

#endif		/* !_HTTPD_H */
