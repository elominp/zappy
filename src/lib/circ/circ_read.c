/*
** circ_read.c for  in /home/querat_g/tmp/circ_buffer
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue May 17 18:33:07 2016 querat_g
** Last update Thu May 26 11:14:04 2016 querat_g
*/

#include "circularbuffer.h"

size_t                  t_circ_read(t_circ *c, void *buf, size_t size)
{
  size_t                i;

  if (!c || !c->buf || !size)
    {
      TRACE("Invalid parameter\n");
      return (0);
    }
  i = 0;
  while (i < size && i < c->content)
    {
      ((char*)buf)[i] = c->buf[c->tail];
      CIRC_INC_TAIL(c);
      ++i;
    }
  ((char*)buf)[i] = '\0';
  c->content -= i;
  return (i);
}

size_t                  t_circ_peek(t_circ *c, void *buf, size_t size)
{
  size_t                i;
  size_t                j;

  if (!c || !c->buf || !size)
    {
      TRACE("Invalid parameter\n");
      return (0);
    }
  i = 0;
  j = c->tail;
  while (i < size && i < c->content)
    {
      ((char*)buf)[i] = c->buf[j];
      j = CIRC(c, (j + 1));
      ++i;
    }
  ((char*)buf)[i] = '\0';
  return (i);
}
