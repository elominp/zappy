/*
** add_item.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/t_opt
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 11:10:21 2016 querat_g
** Last update Sat Jun 25 13:55:06 2016 querat_g
*/

#include "server.h"
#include "macros.h"
#include "map.h"

bool
t_map_add_item(t_map *map, enum e_rsrc type, t_coord cd, size_t amount)
{
  t_hash        *hashtile;
  t_item        *item_stack;
  char const    *res_type_str;

  if (!(hashtile = t_map_at(map, cd)))
    return (ERR(RED"couldn't get %ld %ld\n"WHITE, cd.x, cd.y), false);
  if (!(res_type_str = get_rsrc_string_from_enum(type)))
    {
      DEBUG(RED"invalid resource %d"WHITE, type);
      return (false);
    }
  if ((item_stack = ht_get_entry(hashtile, res_type_str, strlen(res_type_str))))
    {
      item_stack->amount += amount;
      return (true);
    }
  if (!(item_stack = new_t_item(type, amount)))
    return (TRACE("new_t_item() failed"), false);
  if (!ht_add_entry(hashtile, item_stack, res_type_str, strlen(res_type_str)))
    return (TRACE(RED"ht_add_entry failed !"WHITE), false);
  return (true);
}
