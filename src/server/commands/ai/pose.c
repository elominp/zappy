/*
** pose.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:18:59 2016 querat_g
** Last update Tue Jun 21 10:49:31 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

bool
pose(t_cli *c, t_msg *msg)
{
  char const    *what_type;
  t_item        *item;
  t_hash        *tile;

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);
  if (!(msg)                                                              ||
      !(what_type = LIST_FIRST_DATA(msg->params))                         ||
      !(item = ht_get_entry(c->inventory, what_type, strlen(what_type)))  ||
      (item->amount <= 0)                                                 ||
      !(tile = t_map_at(&c->servptr->map, (t_coord){ c->x_pos, c->y_pos })))
    return (ERR(RED"ko\n"WHITE), enqueue_msg(c, "ko\n"), false);
  --item->amount;
  t_map_add_item(&c->servptr->map, get_rsrc_enum_from_string(what_type),
                 (t_coord){ c->x_pos, c->y_pos }, 1);
#ifdef __DEBUG__
  ERR(BLUE"------------------------------------\n"WHITE);
  ht_print(c->inventory, &dump_tile);
  ERR(BLUE"------------------------------------\n"WHITE);
  ht_print(tile, &dump_tile);
  ERR(BLUE"------------------------------------\n"WHITE);
#endif
  pdr(c, get_rsrc_enum_from_string(what_type));
  return (enqueue_msg(c, "ok\n"), true);
}
