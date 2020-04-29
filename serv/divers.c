/*
** divers for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:19:02 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:19:02 PM CEST botton vivien
*/

#include "ftpd.h"

int          site(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}

int          syst(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (215);
}

int          status(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
 return (502);
}

int          help(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (214);
}

int          noop(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (200);
}
