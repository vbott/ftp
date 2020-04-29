/*
** main for ftp in /home/snap/projects/my_ftp/client
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 06:07:18 PM CEST botton vivien
** Last update Sat 02 Apr 2011 06:07:18 PM CEST botton vivien
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "client.h"

static void		close_client(t_client *client)
{
  shutdown(client->ctl_socket, SHUT_RDWR);
  client->stop = 1;
  if (client->file)
    fclose(client->file);
}

static void		init_client(t_client *client)
{
  client->dtp_socket = -1;
  client->open_dtp = active;
  client->file = NULL;
  client->stop = 0;
  client->recv = recv_normal;
  client->send = send_normal;
}

static void		login(t_client *client)
{
  char			buffer[4096];
  int			retcode;

  retcode = 0;
  while (retcode != 230)
  {
    fprintf(stdout, "User : ");
    fgets(buffer, 4095, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    send_cmd("USER", buffer, client);
    if (recv_response(client) != 331)
     continue ;
    fprintf(stdout, "Pass : ");
    fgets(buffer, 4095, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    send_cmd("PASS", buffer, client);
    retcode = recv_response(client);
  }
  send_cmd("SYST", NULL, client);
  recv_response(client);
  send_cmd("TYPE", "I", client);
  recv_response(client);
}

static void		loop_client(t_client *client)
{
  char			*cmd;
  char                  buffer[4096];

  init_client(client);
  if (recv_response(client) != 220)
   exit(EXIT_SUCCESS);
  login(client);
  while (!client->stop)
   {
      fprintf(stdout, "ftp> ");
      cmd = fgets(buffer, 4095, stdin);
      if (!cmd)
	quit("QUIT", NULL, client);
      else
       execute_cmd(buffer, client);
   }
  close_client(client);
}

int  		main(int ac, char **av)
{
  t_client	client;

  if (ac < 2)
   {
     fprintf(stderr, "usage: %s ip [port]\n", av[0]);
     return (EXIT_FAILURE);
   }
  if (!isatty(0))
    return (EXIT_FAILURE);
  client.ctl_socket = connect_to(av[1], ((ac >= 3) ? av[2] : "21"));
  if (client.ctl_socket == -1)
    return (EXIT_FAILURE);
  fprintf(stdout, "Connected to %s.\n", av[1]);
  loop_client(&client);
  return (EXIT_SUCCESS);
}
