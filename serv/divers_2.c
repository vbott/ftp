/*
** divers_2 for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:20:48 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:20:48 PM CEST botton vivien
*/

#include "ftpd.h"

int          smnt(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}

int          quit(char *arg, t_client *client)
{
  (void)(arg);
  client->stop = 1;
  return (221);
}

int          rein(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}

int          type(char *arg, t_client *client)
{
  (void)(client);
  if (!strcmp(arg, "I") || !strcmp(arg, "A"))
    return (200);
  return (504);
}

int          stru(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}
