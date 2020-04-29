/*
** functions for tp in /home/snap/projects/my_ftp/client
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 03 Apr 2011 06:17:47 PM CEST botton vivien
** Last update Sun 03 Apr 2011 06:17:47 PM CEST botton vivien
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "client.h"

void	     remove_fd(t_client *client)
{
  if (client->dtp_socket != -1)
  {
    close(client->dtp_socket);
    client->dtp_socket = -1;
  }
}

void          passive_cmd(char *ftp_cmd, char *arg, t_client *client)
{
 (void)(ftp_cmd);
 (void)(arg);
  if (client->open_dtp == active)
   {
     fprintf(stdout, "Passive mode on.\n");
     client->open_dtp = passive;
   }
  else
   {
     fprintf(stdout, "Passive mode off.\n");
     client->open_dtp = active;
   }
}

void          	generic(char *ftp_cmd, char *arg, t_client *client)
{
 send_cmd(ftp_cmd, arg, client);
 recv_response(client);
}

void          	quit(char *ftp_cmd, char *arg, t_client *client)
{
 generic(ftp_cmd, arg, client);
 client->stop = 1;
}

