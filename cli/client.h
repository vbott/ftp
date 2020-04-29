/*
** client for ftp in /home/snap/projects/my_ftp/client
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 06:14:27 PM CEST botton vivien
** Last update Sat 02 Apr 2011 06:14:27 PM CEST botton vivien
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdio.h>

typedef struct s_client
{
  void		(*open_dtp)(struct s_client*);
  int		ctl_socket;
  int		dtp_socket;
  FILE          *file;
  int		stop;
  int		(*recv)(struct s_client*, void*, size_t);
  int           (*send)(struct s_client*, void*, size_t);
}		t_client;

typedef struct	s_cmd
{
  char          *cmd;
  char		*ftp_cmd;
  int		nb_args;
  int		mandatory;
  void          (*func)(char *ftp_cmd, char *arg, t_client*);
}		t_cmd;

/* utils.c */
int             connect_to(char *addr, char *port);
int             listen_to(char *port);

/* control_op.c */
int             send_normal(t_client *client, void *buffer, size_t size);
int             recv_normal(t_client *client, void *buffer, size_t size);
int             send_dtp(t_client *client, void *buffer, size_t size);
int             recv_dtp(t_client *client, void *buffer, size_t size);

/* port_pasv.c */
void		passive(t_client *);
void		active(t_client *);

/* cmd.c */
int		recv_response(t_client *);
void            send_cmd(char *cmd, char *data, t_client *client);
void		execute_cmd(char*, t_client*);

/* functions.c */
void          remove_fd(t_client *client);
void          passive_cmd(char *ftp_cmd, char *arg, t_client*);
void          generic(char *ftp_cmd, char *arg, t_client*);
void          quit(char *ftp_cmd, char *arg, t_client*);
void          retr(char *ftp_cmd, char *arg, t_client*);
void          stor(char *ftp_cmd, char *arg, t_client*);
void          appe(char *ftp_cmd, char *arg, t_client*);
void          rnfr(char *ftp_cmd, char *arg, t_client*);
void          list(char *ftp_cmd, char *arg, t_client*);
void          nlst(char *ftp_cmd, char *arg, t_client*);
void          local_list(char *ftp_cmd, char *arg, t_client*);
void          local_cd(char *ftp_cmd, char *arg, t_client*);
void          local_pwd(char *ftp_cmd, char *arg, t_client*);
void          help(char *ftp_cmd, char *arg, t_client*);

#endif /* _CLIENT_ */
