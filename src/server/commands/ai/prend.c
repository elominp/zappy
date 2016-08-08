/*
** prend.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:18:05 2016 querat_g
** Last update Sun Jun 26 12:12:29 2016 schmou_a
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static  char g_buff[1024];
static  int g_i = 0;
static  int g_randx = 0;
static  int g_randy = 0;

static int
get_object(t_hash *tile, char *obj_name)
{
  t_item        *it;
  int           ret;

  if (!(it = ht_get_entry(tile, obj_name, strlen(obj_name))))
    {
      ret = snprintf(g_buff + g_i, sizeof(g_buff) - g_i, "0 ");
      ERR(GREEN"ret %d\n"WHITE, ret);
      return (ret);
    }
  ret = snprintf(g_buff + g_i, sizeof(g_buff) - g_i, "%lu ", it->amount);
  ERR(GREEN"ret %d\n"WHITE, ret);
  return (ret);
}

static void
get_tile(void *client)
{
  t_hash        *tile;
  t_coord	pos;
  t_cli		*c;

  c = (t_cli *)client;
  if (c->is_graphic)
    {
      pos.x = g_randx;
      pos.y = g_randy;
      if ((tile = t_map_at(&c->servptr->map, pos)) == NULL)
	{
	  ERR(RED"bct : invalid coordinates\n"WHITE);
	  return ;
	}
      g_i = snprintf(g_buff, sizeof(g_buff) - g_i, "bct %ld %ld ", pos.x, pos.y);
      g_i += get_object(tile, "nourriture");
      g_i += get_object(tile, "linemate");
      g_i += get_object(tile, "deraumere");
      g_i += get_object(tile, "sibur");
      g_i += get_object(tile, "mendiane");
      g_i += get_object(tile, "phiras");
      g_i += get_object(tile, "thystame");
      snprintf(g_buff + g_i, sizeof(g_buff) - g_i, "\n");
      enqueue_msg(c, g_buff);
    }
}

static void
repop_resource(enum e_rsrc type, t_serv *server)
{
  g_randx = rand() % server->map.width;
  g_randy = rand() % server->map.height;
  t_map_add_item(&server->map,
                 type,
                 (t_coord){g_randx, g_randy},
                 1);
  ht_foreach(server->clients, &get_tile);
}

bool
prend(t_cli *c, t_msg *msg)
{
  char const    *what_type;
  t_item        *item;

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);
  if (!(msg) || !(what_type = LIST_FIRST_DATA(msg->params)) ||
      !t_map_take_item(&c->servptr->map,
                       get_rsrc_enum_from_string(what_type),
                       (t_coord){ c->x_pos, c->y_pos }, 1))
    return (ERR(RED"ko\n"WHITE), enqueue_msg(c, "ko\n"), false);
  pgt(c, get_rsrc_enum_from_string(what_type));
  if ((item = ht_get_entry(c->inventory, what_type, strlen(what_type))))
    {
      ++item->amount;
      repop_resource(get_rsrc_enum_from_string(what_type), c->servptr);
      return (enqueue_msg(c, "ok\n"), true);
    }
  if (!(item = new_t_item(get_rsrc_enum_from_string(what_type), 1)))
    return (TRACE(RED"new_t_item() failed"WHITE), false);
  if (!ht_add_entry(c->inventory, item, what_type, strlen(what_type)))
    return (TRACE(RED"new_t_item() failed"WHITE), free(item), false);
  ht_print(c->inventory, &dump_tile);
  repop_resource(get_rsrc_enum_from_string(what_type), c->servptr);
  return (enqueue_msg(c, "ok\n"), true);
}
