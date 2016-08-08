/*
** at.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Jun 12 14:33:52 2016 querat_g
** Last update Mon Jun 13 16:54:52 2016 querat_g
*/

#include "map.h"
#include "macros.h"

t_hash
*t_map_at(t_map *map, t_coord c)
{
  if (!map || map->width <= 0 || map->height <= 0)
    return (NULL);

  c.x = (c.x < 0)
    ? (((map->width) + ((c.x))) % map->width)
    : c.x % map->width;

  c.y = (c.y < 0)
    ? (((map->height) + ((c.y))) % map->height)
    : c.y % map->height;

  return (map->map[c.y][c.x]);
}
