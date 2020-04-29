/*
** cd for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:19:57 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:19:57 PM CEST botton vivien
*/

#define	 _BSD_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include "ftpd.h"

int          cwd(char *arg, t_client *client)
{
  char	     save[512];
  char	     new[512];

  getcwd(save, 512);
  if (chdir(arg) == -1)
    return (550);
  getcwd(new, 512);
  if (strncmp(client->root, new, strlen(client->root)))
  {
    chdir(save);
    return (550);
  }
  return (250);
}

int          cdup(char *arg, t_client *client)
{
  (void)(arg);
  return (cwd("..", client));
}
