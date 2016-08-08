/*
** circ_write.c for  in /home/querat_g/tmp/circ_buffer
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue May 17 18:31:56 2016 querat_g
** Last update Wed May 25 09:20:38 2016 querat_g
*/

#include "circularbuffer.h"

static size_t           circular_write(t_circ *c, void *mem, size_t size)
{
  size_t                i;

  i = 0;
  while (i < size && (c->content + i) < c->size)
    {
      c->buf[CIRC(c, c->head)] = ((char*)mem)[i];
      CIRC_INC_HEAD(c);
      ++i;
    }
  c->content += i;
  return (i);
}

size_t                  t_circ_write(t_circ *c, void *mem, size_t size)
{
  if (!c || !c->buf)
    return (TRACE("invalid t_circ pointer exception\n"), false);
  return (circular_write(c, mem, size));
}

static size_t           circular_overwrite(t_circ *c, void *mem, size_t size)
{
  size_t                i;

  i = 0;
  while (i < size)
    {
      c->buf[CIRC(c, c->head)] = ((char*)mem)[i];
      CIRC_INC_HEAD(c);
      ++i;
    }
  c->content += i;
  return (i);
}

size_t                  t_circ_overwrite(t_circ *c, void *mem, size_t size)
{
  if (!c || !c->buf)
    return (TRACE("invalid t_circ pointer exception\n"), false);
  return (circular_overwrite(c, mem, size));
}
