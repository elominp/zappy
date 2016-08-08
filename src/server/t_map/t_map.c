/*
** t_map.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/t_opt
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 09:36:41 2016 querat_g
** Last update Sun Jun 12 18:22:27 2016 querat_g
*/

#include <stdbool.h>
#include "macros.h"
#include "map.h"

bool
t_map_dest(t_map *map)
{
  int64_t       x;
  int64_t       y;

  if (map->map)
    {
      for (y = 0; y < map->height && map->map[y]; ++y)
        {
          for (x = 0; x < map->width && map->map[y][x]; ++x)
            ht_free(map->map[y][x], &free);
          free(map->map[y]);
        }
      free(map->map);
    }
  ZERO_MEM(map);
  return (false);
}

bool
t_map_const(t_map *map, size_t width, size_t height)
{
  size_t        x;
  size_t        y;

  if (!map)
    return (false);
  map->width = width;
  map->height = height;
  if (!(map->map = calloc((height + 1), sizeof(t_hash**))))
    return (perror("calloc()"), false);

  for (y = 0; y < height; ++y)
    {
      if (!(map->map[y] = calloc(width + 1, sizeof(t_hash*))))
        return (perror("calloc()"), t_map_dest(map), false);
      for (x = 0; x < width; ++x)
        {
          if (!(map->map[y][x] = ht_init(2)))
            return (TRACE("ht_init() failed"), t_map_dest(map), false);
        }
    }

  return (true);
}
