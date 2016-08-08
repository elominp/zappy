/*
** make_coord.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 17:27:53 2016 querat_g
** Last update Sat Jun 11 17:29:56 2016 querat_g
*/

#include "server.h"
#include "map.h"
#include "macros.h"

t_coord
make_t_coord(size_t x, size_t y)
{
  t_coord       crd;

  crd.x = x;
  crd.y = y;
  return (crd);
}
