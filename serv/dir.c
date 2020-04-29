/*
** dir for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:20:38 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:20:38 PM CEST botton vivien
*/

#define  _BSD_SOURCE
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "ftpd.h"

int          dele(char *arg, t_client *client)
{
  (void)(client);
  if (unlink(arg) == -1)
    return ((errno == EBUSY)  ? 450 : 550);
  else
    return (250);
}

int          rmd(char *arg, t_client *client)
{
  (void)(client);
  if (rmdir(arg) == -1)
    return ((errno == EBUSY)  ? 450 : 550);
  else
    return (250);
}

int          mkd(char *arg, t_client *client)
{
  (void)(client);
  if (mkdir(arg, 0744) == -1)
    return (550);
  else
    return (250);
}

int          pwd(char *arg, t_client *client)
{
  char	     buffer[512];
  char	     *wd;

  (void)(arg);
  wd = getcwd(NULL, 0);
  if (wd == NULL)
    return (550);
  snprintf(buffer, 512, "\"%s\" is current directory", wd);
  answer(257, buffer, client);
  free(wd);
  return (0);
}
