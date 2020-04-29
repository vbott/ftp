/*
** list for ftp in /home/snap/projects/my_ftp/client
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 03 Apr 2011 10:17:29 PM CEST botton vivien
** Last update Sun 03 Apr 2011 10:17:29 PM CEST botton vivien
*/

#include <stdio.h>
#include <unistd.h>
#include "client.h"

void          	list(char *ftp_cmd, char *arg, t_client *client)
{
 char		buffer[4096];
 size_t		readed;
 int		ret;

 client->open_dtp(client);
 send_cmd(ftp_cmd, arg, client);
 ret = recv_response(client);
 if (ret == 150)
   {
     readed = recv_dtp(client, buffer, 4096);
     while (readed > 0)
     {
       fwrite(buffer, 1, readed, stdout);
       readed = recv_dtp(client, buffer, 4096);
     }
   }
 close(client->dtp_socket);
 client->dtp_socket = -1;
 if (ret == 150)
  recv_response(client);
}

void          	nlst(char *ftp_cmd, char *arg, t_client *client)
{
 (void)(ftp_cmd);
 list("NLST", arg, client);
}

