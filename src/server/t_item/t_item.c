/*
** t_item.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 14:43:06 2016 querat_g
** Last update Sat Jun 11 15:01:32 2016 querat_g
*/

#include "zappy.h"
#include "macros.h"

void
t_item_dest(t_item *item)
{
  ZERO_MEM(item);
}

void
t_item_const(t_item *item, enum e_rsrc type, uint32_t amount)
{
  if (!item)
    return ;
  ZERO_MEM(item);
  item->type = type;
  item->amount = amount;
}

t_item
*new_t_item(enum e_rsrc type, uint32_t amount)
{
  t_item        *item;

  if (!(item = malloc(sizeof(*item))))
    return (perror("malloc"), NULL);
  t_item_const(item, type, amount);
  return (item);
}
