/*
** take_item.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Jun 12 11:32:09 2016 querat_g
** Last update Sun Jun 12 18:15:28 2016 querat_g
*/

#include "server.h"
#include "macros.h"
#include "map.h"

static bool
delete_item_stack(t_hash *hash, char const *type_str)
{
  if (!type_str || !hash)
    return (false);
  ht_rm_entry(hash, type_str, strlen(type_str), &free);
  return (true);
}

size_t
t_map_take_item(t_map *map, enum e_rsrc type, t_coord cd, size_t amount)
{
  t_hash        *hashtile;
  t_item        *item_stack;
  char const    *res_type_str;

  if (!(hashtile = t_map_at(map, cd)))
    return (0);
  if (!(res_type_str = get_rsrc_string_from_enum(type)))
    {
      DEBUG(RED"invalid resource %d"WHITE, type);
      return (0);
    }
  item_stack = ht_get_entry(hashtile, res_type_str, strlen(res_type_str));
  if (!item_stack)
    return (0);
  if (amount >= item_stack->amount)
    {
      amount = item_stack->amount;
      item_stack->amount = 0;
      delete_item_stack(hashtile, res_type_str);
      return (amount);
    }
  item_stack->amount -= amount;
  return (amount);
}
