/*
** xfunctions for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:22:05 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:22:05 PM CEST botton vivien
*/

#include <unistd.h>
#include <stdlib.h>

void	*xmalloc(size_t size)
{
  void	*ptr;

  ptr = malloc(size);
  if (!ptr)
    exit(EXIT_FAILURE);
  return (ptr);
}
