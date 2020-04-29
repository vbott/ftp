/*
** file for fptd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:19:20 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:19:20 PM CEST botton vivien
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include "ftpd.h"

int          retr(char *arg, t_client *client)
{
  struct epoll_event    ev;
  t_sockfunc            *tmp;

  if (client->dtp.file != NULL)
    return (550);
  if (client->dtp.socket == -1)
    return (425);
  client->dtp.file = fopen(arg, "r");
  if (client->dtp.file == NULL)
    return (550);
  fseek(client->dtp.file, client->dtp.bit_pos, SEEK_SET);
  client->dtp.bit_pos = 0;
  tmp = xmalloc(sizeof(*tmp));
  tmp->in = NULL;
  tmp->hangup = hangup_file;
  tmp->out = send_file;
  ev.events = EPOLLOUT | EPOLLHUP;
  ev.data.u64 = 0;
  ev.data.ptr = tmp;
  epoll_ctl(client->epoll_fd, EPOLL_CTL_ADD, client->dtp.socket, &ev);
  return (150);
}

int          stor(char *arg, t_client *client)
{
  struct epoll_event    ev;
  t_sockfunc            *tmp;

  if (client->dtp.file != NULL)
    return (550);
  if (client->dtp.socket == -1)
    return (425);
  client->dtp.file = fopen(arg, "w");
  if (client->dtp.file == NULL)
    return (550);
  fseek(client->dtp.file, client->dtp.bit_pos, SEEK_SET);
  client->dtp.bit_pos = 0;
  tmp = xmalloc(sizeof(*tmp));
  tmp->in = recv_file;
  tmp->hangup = hangup_file;
  tmp->out = NULL;
  ev.events = EPOLLIN | EPOLLHUP;
  ev.data.u64 = 0;
  ev.data.ptr = tmp;
  epoll_ctl(client->epoll_fd, EPOLL_CTL_ADD, client->dtp.socket, &ev);
  return (150);
}

int          stou(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}

int          appe(char *arg, t_client *client)
{
  struct epoll_event    ev;
  t_sockfunc            *tmp;

  if (client->dtp.file != NULL)
    return (550);
  if (client->dtp.socket == -1)
    return (425);
  client->dtp.file = fopen(arg, "a");
  if (client->dtp.file == NULL)
    return (550);
  client->dtp.bit_pos = 0;
  tmp = xmalloc(sizeof(*tmp));
  tmp->in = recv_file;
  tmp->hangup = hangup_file;
  tmp->out = NULL;
  ev.events = EPOLLIN | EPOLLHUP;
  ev.data.u64 = 0;
  ev.data.ptr = tmp;
  epoll_ctl(client->epoll_fd, EPOLL_CTL_ADD, client->dtp.socket, &ev);
  return (150);
}
