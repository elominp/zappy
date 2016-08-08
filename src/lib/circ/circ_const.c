/*
** const.c for  in /home/querat_g/tmp/circ_buffer
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue May 17 18:29:46 2016 querat_g
** Last update Sun May 22 14:14:54 2016 querat_g
*/

#include "circularbuffer.h"

bool                    t_circ_const(t_circ *c, size_t size)
{
  ASSERT(c != NULL && size > 0);
  if (!c || !size)
    return (ERR("t_circ_const\n"), false);
  ZERO_MEM(c);
  c->size = size;
  c->buf = calloc(sizeof(char), size + 1);
  if (!c->buf)
    return (t_circ_dest(c));

  c->print = &t_circ_print;
  c->write = &t_circ_write;
  c->overwrite = &t_circ_overwrite;
  c->read = &t_circ_read;
  c->peek = &t_circ_peek;

  return (true);
}

t_circ                  *new_t_circ(size_t size)
{
  t_circ                *circ;

  if (!size)
    return (NULL);
  circ = calloc(sizeof(t_circ), 1);
  return (t_circ_const(circ, size) ? circ : NULL);
}
