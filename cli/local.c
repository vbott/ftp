/*
** local for ftp in /home/snap/projects/my_ftp/client
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 03 Apr 2011 10:14:41 PM CEST botton vivien
** Last update Sun 03 Apr 2011 10:14:41 PM CEST botton vivien
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "client.h"

void          	local_list(char *ftp_cmd, char *arg, t_client *client)
{
  pid_t		pid;

  (void)(client);
  (void)(ftp_cmd);
  pid = fork();
  if (pid == 0)
    execlp("ls", "ls", "-lA", arg, NULL);
  else if (pid != -1)
    waitpid(pid, NULL, 0);
}

void          	local_cd(char *ftp_cmd, char *arg, t_client *client)
{
  if (chdir(arg) == -1)
   perror("cd");
  local_pwd(ftp_cmd, arg, client);
}

void          	local_pwd(char *ftp_cmd, char *arg, t_client *client)
{
  char		*path;

  (void)(arg);
  (void)(client);
  (void)(ftp_cmd);
  path = getcwd(NULL, 0);
  fprintf(stdout, "Local directory is %s\n", path);
  free(path);
}
