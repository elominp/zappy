/*
** circular.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 21 11:36:10 2016 querat_g
** Last update Tue Jun 21 11:36:18 2016 querat_g
*/

#include "server.h"

void
circular(t_map *map, t_coord *c)
{
  c->x = (c->x < 0)
    ? ((c->x % map->width) * (-1))
    : (c->x % map->width);
  c->y = (c->y < 0)
    ? ((c->y % map->height) * (-1))
    : (c->y % map->height);
}
