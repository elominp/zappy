/*
** take_from_client.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 21 16:19:33 2016 querat_g
** Last update Thu Jun 23 16:03:31 2016 querat_g
*/

#include "server.h"
#include "client.h"
#include "zappy.h"

int
take_from_client(t_cli *c, enum e_rsrc type, int quantity)
{
  t_item        *item;
  char const    *str;
  int           ret;

  if (!c || !c->inventory || quantity <= 0                      ||
      !(str = get_rsrc_string_from_enum(type))                  ||
      !(item = ht_get_entry(c->inventory, str, strlen(str)))    ||
      (item->amount <= 0))
    return (0);

  if (item->amount < ((uint)quantity))
    {
      ret = item->amount;
      item->amount = 0;
      return (ret);
    }
  else
    item->amount -= quantity;
  return (quantity);
}

int
give_to_client(t_cli *c, enum e_rsrc type, int quantity)
{
  t_item        *item;
  char const    *str;

  if (!c || !c->inventory || quantity <= 0                      ||
      !(str = get_rsrc_string_from_enum(type)))
    return (0);

  if (!(item = ht_get_entry(c->inventory, str, strlen(str))))
    {
      if (!(item = new_t_item(type, quantity)))
        return (TRACE("new_t_item() failed"), 0);
      if (!ht_add_entry(c->inventory, item, str, strlen(str)))
        return (TRACE("ht_add_entry() failed"), free(item), 0);
    }
  else
    item->amount += quantity;

  return (quantity);
}
