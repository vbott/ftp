/*
** file_edit for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:13 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:13 PM CEST botton vivien
*/

#define	 _BSD_SOURCE
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "ftpd.h"

int          allo(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}

int          rest(char *arg, t_client *client)
{
  client->dtp.bit_pos = atoi(arg);
  if (client->dtp.bit_pos < 0)
    {
      client->dtp.bit_pos = 0;
      return (501);
    }
  return (350);
}

int          rnfr(char *arg, t_client *client)
{
  client->data = strdup(arg);
  return (350);
}

int          rnto(char *arg, t_client *client)
{
  int	     ret;

  if (rename(client->data, arg))
    ret = ((errno == EBUSY)  ? 450 : 550);
  else
    ret = (250);
  free(client->data);
  client->data = NULL;
  return (ret);
}

int          abor(char *arg, t_client *client)
{
  (void)(arg);
  if (client->dtp.socket != -1)
    return (550);
  remove_fd(client);
  if (client->dtp.file)
   {
     fclose(client->dtp.file);
     client->dtp.file = NULL;
   }
  return (226);
}

