/*
** cmd for my_ftp in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 04:38:37 PM CEST botton vivien
** Last update Sat 02 Apr 2011 04:38:37 PM CEST botton vivien
*/

#include <strings.h>
#include "ftpd.h"

static const t_cmd  gl_cmd[] = {
  {"AUTH", 1, 1, 0, NULL, auth},
  {"USER", 1, 1, 0, NULL, user},
  {"PASS", 1, 1, 0, &gl_cmd[1], pass},
  {"ACCT", 1, 1, 0, &gl_cmd[2], account},
  {"CWD", 1, 1, 1, NULL, cwd},
  {"CDUP", 0, 1, 1, NULL, cdup},
  {"SMNT", 1, 1, 1, NULL, smnt},
  {"QUIT", 0, 1, 0, NULL, quit},
  {"REIN", 0, 1, 1, NULL, rein},
  {"PORT", 1, 1, 1, NULL, port},
  {"PASV", 0, 1, 1, NULL, pasv},
  {"TYPE", 1, 1, 1, NULL, type},
  {"STRU", 1, 1, 1, NULL, stru},
  {"MODE", 1, 1, 1, NULL, mode},
  {"RETR", 1, 1, 1, NULL, retr},
  {"STOR", 1, 1, 1, NULL, stor},
  {"STOU", 0, 1, 1, NULL, stou},
  {"APPE", 1, 1, 1, NULL, appe},
  {"ALLO", 1, 1, 1, NULL, allo},
  {"REST", 1, 1, 1, NULL, rest},
  {"RNFR", 1, 1, 1, NULL, rnfr},
  {"RNTO", 1, 1, 1, &gl_cmd[20], rnto},
  {"ABOR", 0, 1, 1, NULL, abor},
  {"DELE", 1, 1, 1, NULL, dele},
  {"RMD", 1, 1, 1, NULL, rmd},
  {"MKD", 1, 1, 1, NULL, mkd},
  {"PWD", 0, 1, 1, NULL, pwd},
  {"LIST", 1, 0, 1, NULL, list},
  {"NLST", 1, 0, 1, NULL, nlst},
  {"SITE", 1, 1, 1, NULL, site},
  {"SYST", 0, 1, 0, NULL, syst},
  {"STAT", 1, 0, 1, NULL, status},
  {"HELP", 1, 0, 0, NULL, help},
  {"NOOP", 0, 1, 0, NULL, noop},
  {NULL, 0, 0, 0, NULL, NULL}
};

static void		get_cmd_and_args(char *buffer, char **cmd, char **arg)
{
  int			i;

  for (i = 0; buffer[i] && buffer[i] != ' '
      && buffer[i] != '\r'
      && buffer[i] != '\n'; ++i);
  if (buffer[i])
  {
    buffer[i] = '\0';
    *cmd = buffer;
    *arg = &buffer[i + 1];
    ++i;
    for ( ; buffer[i] && buffer[i] != '\n' && buffer[i] != '\r'; ++i);
    buffer[i] = '\0';
    if ((*arg)[0] == '\0')
      *arg = NULL;
  }
  else
  {
    *cmd = NULL;
    *arg = NULL;
  }
}

static	int		is_valid(int i, char *arg, t_cmd const  *last,
	       		t_client *client)
{
  int			valid;

  valid = 0;
  if (gl_cmd[i].authenticated > client->authenticated)
    answer(530, NULL, client);
  else if (!arg && gl_cmd[i].nb_args > 0 && gl_cmd[i].mandatory)
    answer(501, NULL, client);
  else if (arg && gl_cmd[i].nb_args == 0)
    answer(501, NULL, client);
  else if (gl_cmd[i].prev && gl_cmd[i].prev != last)
    answer(503, NULL, client);
  else
    valid = 1;
  return (valid);
}

void			treat_cmd(t_client *client, t_sockfunc *sf)
{
  int		readed;
  char		buffer[4096];
  char		*cmd;
  char		*arg;
  int		ret;
  static t_cmd	const	*last = NULL;
  int		i;

  (void)(sf);
  readed = client->recv(client, buffer, 4095);
  if (readed == -1 || readed == 0)
   exit(EXIT_FAILURE);
  buffer[readed] = '\0';
  get_cmd_and_args(buffer, &cmd, &arg);
  for (i = 0; cmd && gl_cmd[i].cmd && strcasecmp(cmd, gl_cmd[i].cmd); i++);
  if (!gl_cmd[i].cmd)
    answer(500, NULL, client);
  else if (is_valid(i, arg, last, client))
  {
    ret = gl_cmd[i].func(arg, client);
    if (ret)
      answer(ret, NULL, client);
    last = &gl_cmd[i];
  }
}
