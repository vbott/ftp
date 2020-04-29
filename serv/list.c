/*
** list for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:18:32 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:18:32 PM CEST botton vivien
*/

#define	 _BSD_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <unistd.h>
#include "ftpd.h"

int          list(char *arg, t_client *client)
{
  struct epoll_event    ev;
  t_sockfunc            *tmp;
  char			buffer[512];

  if (client->dtp.file != NULL)
    return (550);
  if (client->dtp.socket == -1)
    return (425);
  if (arg && (!strcasecmp(arg, "aL") || !strcasecmp(arg, "-aL")))
     arg = NULL;
  if (arg && (getcwd(buffer, 512) == NULL || chdir(arg) == -1))
    return (550);
  client->dtp.file = popen("ls -lA | sed 's/$/\r/g'", "r");
  if (arg)
    chdir(buffer);
  if (client->dtp.file == NULL)
    return (550);
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

int          nlst(char *arg, t_client *client)
{
  struct epoll_event    ev;
  t_sockfunc            *tmp;
  char                  buffer[512];

  if (client->dtp.file != NULL)
    return (550);
  if (client->dtp.socket == -1)
    return (425);
  if (arg && (!strcasecmp(arg, "aL") || !strcasecmp(arg, "-aL")))
     arg = NULL;
  if (arg && (getcwd(buffer, 512) == NULL || chdir(arg) == -1))
    return (550);
  client->dtp.file = popen("ls -1 | sed 's/$/\r/g'", "r");
  if (arg)
    chdir(buffer);
  if (client->dtp.file == NULL)
    return (550);
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
