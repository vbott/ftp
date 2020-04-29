/*
** file for ftp in /home/snap/projects/my_ftp/client
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 03 Apr 2011 10:16:27 PM CEST botton vivien
** Last update Sun 03 Apr 2011 10:16:27 PM CEST botton vivien
*/

#include <stdio.h>
#include <unistd.h>
#include "client.h"

void          	retr(char *ftp_cmd, char *arg, t_client *client)
{
 char		buffer[4096];
 size_t		readed;
 int		ret;

 client->file = fopen(arg, "w");
 if (client->file == NULL)
    return ;
 client->open_dtp(client);
 send_cmd(ftp_cmd, arg, client);
 ret = recv_response(client);
 if (ret == 150 && client->dtp_socket != -1)
   {
     readed = recv_dtp(client, buffer, 4096);
     while (!ferror(client->file) && readed > 0)
     {
       fwrite(buffer, 1, readed, client->file);
       readed = recv_dtp(client, buffer, 4096);
     }
   }
 close(client->dtp_socket);
 client->dtp_socket = -1;
 fclose(client->file);
 client->file = NULL;
 if (ret == 150)
   recv_response(client);
}

void          	stor(char *ftp_cmd, char *arg, t_client *client)
{
 char		buffer[4096];
 size_t		readed;
 int		ret;

 client->file = fopen(arg, "r");
 if (client->file == NULL)
    return ;
 client->open_dtp(client);
 send_cmd(ftp_cmd, arg, client);
 ret = recv_response(client);
 if (ret == 150 && client->dtp_socket != -1)
   while (!ferror(client->file) && !feof(client->file))
    {
      readed = fread(buffer, 1, 4096, client->file);
      send_dtp(client, buffer, readed);
    }
 close(client->dtp_socket);
 client->dtp_socket = -1;
 fclose(client->file);
 client->file = NULL;
 if (ret == 150)
   recv_response(client);
}

void          	appe(char *ftp_cmd, char *arg, t_client *client)
{
  (void)(ftp_cmd);
  stor("APPE", arg, client);
}

void          	rnfr(char *ftp_cmd, char *arg, t_client *client)
{
 send_cmd(ftp_cmd, arg, client);
 recv_response(client);
}
