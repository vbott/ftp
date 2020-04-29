/*
** cmd for ftp in /home/snap/projects/my_ftp/client
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 03 Apr 2011 05:27:24 PM CEST botton vivien
** Last update Sun 03 Apr 2011 05:27:24 PM CEST botton vivien
*/

#define  _BSD_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

static const t_cmd  gl_cmd[] = {
  {"passive", NULL, 0, 1, passive_cmd},
  {"cd", "CWD", 1, 1, generic},
  {"cdup", "CDUP", 0, 1, generic},
  {"quit", "QUIT", 0, 1, quit},
  {"get", "RETR", 1, 1, retr},
  {"put", "STOR", 1, 1, stor},
  {"append", "APPE", 1, 1, appe},
  {"rename", "RNFR", 1, 1, rnfr},
  {"delete", "DELE", 1, 1, generic},
  {"rmdir", "RMD", 1, 1, generic},
  {"mkdir", "MKD", 1, 1, generic},
  {"pwd", "PWD", 0, 1, generic},
  {"ls", "LIST", 1, 0, list},
  {"nlist", "NLST", 1, 0, nlst},
  {"system", "SYST", 0, 1, generic},
  {"lls", NULL, 1, 0, local_list},
  {"lcd", NULL, 1, 1, local_cd},
  {"lpwd", NULL, 1, 0, local_pwd},
  {"help", NULL, 1, 0, help},
  {"rhelp", "HELP", 1, 0, generic},
  {NULL, NULL, 0, 0, NULL}
};

void			send_cmd(char *cmd, char *data, t_client *client)
{
  char                  buffer[512];
  int			size;

  if (data)
   size = snprintf(buffer, 512, "%s %s\r\n", cmd, data);
  else
   size = snprintf(buffer, 512, "%s \r\n", cmd);
  client->send(client, buffer, size);
}

int			recv_response(t_client *client)
{
  char			buffer[4096];
  int			readed;

  readed = client->recv(client, buffer, 4095);
  if (readed == 0 || readed == -1)
  {
    fprintf(stdout, "Disconnected\n");
    exit(EXIT_SUCCESS);
  }
  write(1, buffer, readed);
  buffer[readed] = '\0';
  return (strtol(buffer, NULL, 10));
}

static	int		is_valid(int i, char *arg)
{
  int			valid;

  valid = 0;
  if (!arg && gl_cmd[i].nb_args > 0 && gl_cmd[i].mandatory)
    fprintf(stdout, "Missing argument.\n");
  else if (arg && gl_cmd[i].nb_args == 0)
    fprintf(stdout, "Too many argument.\n");
  else
    valid = 1;
  return (valid);
}

void			execute_cmd(char *buffer, t_client *client)
{
  char			*cmd;
  char			*arg;
  int			i;

  buffer[strlen(buffer) -1 ] = '\0';
  cmd = strtok(buffer, " ");
  arg = strtok(NULL, " ");
  if ((arg && strtok(NULL, " ")) || !cmd)
   {
     fprintf(stdout, "Syntax Error.\n");
     return ;
   }
  for (i = 0; gl_cmd[i].cmd && strcasecmp(cmd, gl_cmd[i].cmd); i++);
  if (gl_cmd[i].cmd && is_valid(i, arg))
     gl_cmd[i].func(gl_cmd[i].ftp_cmd, arg, client);
  else if (!gl_cmd[i].cmd)
   fprintf(stdout, "Unknow command.\n");
}

void			help(char *ftp_cmd, char *arg, t_client *client)
{
  int			i;

  (void)(arg);
  (void)(client);
  (void)(ftp_cmd);
  for (i = 0; gl_cmd[i].cmd; i++)
  {
    fprintf(stdout, "%s\t", gl_cmd[i].cmd);
    if (i % 4 == 0 && i != 0)
     fprintf(stdout, "\n");
  }
  fprintf(stdout, "\n");
}

