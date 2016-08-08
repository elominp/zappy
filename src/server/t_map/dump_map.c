/*
** dump_map.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 15:06:08 2016 querat_g
** Last update Sun Jun 12 17:47:02 2016 querat_g
*/

#include "macros.h"
#include "map.h"

void
dump_tile(void *t)
{
  t_item        *item_stack;

  if (!(item_stack = t))
    return ;
  ERR(BROWN"    -> Type: %s Amount: %zu\n"WHITE,
      get_rsrc_string_from_enum(item_stack->type),
      item_stack->amount);
}

bool
dump_map(t_map *map)
{
  size_t        x;
  size_t        y;

  for (y = 0; map->map[y]; ++y)
    for (x = 0; map->map[y][x]; ++x)
      {
        ERR(BLUE"DUMPING TILE -----------------\n"WHITE
            "y:%zu, x:%zu\n", y, x);
        ht_foreach(map->map[y][x], &dump_tile);
        ERR(BLUE"!-----------------------------\n"WHITE);
      }

  return (true);
}
