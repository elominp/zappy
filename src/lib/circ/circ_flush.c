/*
** circ_flush.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common/lib/circ
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 21 18:38:47 2016 querat_g
** Last update Sat May 21 18:44:01 2016 querat_g
*/

#include "circularbuffer.h"

void    t_circ_clear(t_circ *c)
{
  c->content = 0;
  memset(c->buf, 0, c->size);
}
