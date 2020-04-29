/*
** functions for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:23 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:23 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <unistd.h>
#include <fcntl.h>
#include "ftpd.h"

int          mode(char *arg, t_client *client)
{
  (void)(arg);
  (void)(client);
  return (502);
}

void	     hangup_file(t_client *client, t_sockfunc *sf)
{
  answer(426, NULL, client);
  fclose(client->dtp.file);
  free(sf);
  client->dtp.file = NULL;
  remove_fd(client);
}

void	     send_file(t_client *client, t_sockfunc *sf)
{
  char	     buffer[4096];
  size_t     readed;

  readed = fread(buffer, 1, 4096, client->dtp.file);
  if (!ferror(client->dtp.file))
    client->dtp.send(&client->dtp, buffer, readed);
  if (ferror(client->dtp.file) || feof(client->dtp.file))
   {
     if (feof(client->dtp.file))
	answer(226, NULL, client);
     else
	answer(451, NULL, client);
     fclose(client->dtp.file);
     client->dtp.file = NULL;
     free(sf);
     remove_fd(client);
   }
}

void	     recv_file(t_client *client, t_sockfunc *sf)
{
  char	     buffer[4096];
  int	     readed;

  readed = client->dtp.recv(&client->dtp, buffer, 4096);
  if (readed != -1)
    fwrite(buffer, readed, 1, client->dtp.file);
  if (readed == -1 || ferror(client->dtp.file))
  {
    answer(451, NULL, client);
    readed = -1;
  }
  if (readed < 4096)
   {
     if (readed != -1)
	answer(226, NULL, client);
     fclose(client->dtp.file);
     client->dtp.file = NULL;
     free(sf);
     remove_fd(client);
   }
}

