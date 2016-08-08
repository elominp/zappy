/*
** circ_dest.c for  in /home/querat_g/tmp/circ_buffer
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue May 17 18:28:31 2016 querat_g
** Last update Sat May 21 13:46:31 2016 querat_g
*/

#include "circularbuffer.h"

bool                    t_circ_dest(t_circ *c)
{
  if (!c)
    return (false);
  if (c->buf)
    free(c->buf);
  ZERO_MEM(c);
  return (false);
}

t_circ                  *delete_t_circ(t_circ **c)
{
  ASSERT(c != NULL && (*c) != NULL);
  if (!c || !(*c))
    return (NULL);
  t_circ_dest(*c);
  free(*c);
  (*c) = NULL;
  return (NULL);
}
