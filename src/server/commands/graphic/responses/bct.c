/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 23 12:31:19 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static	char g_buff[1024];
static	int g_i = 0;

static int
get_coords(t_cli *c, t_node *param, t_coord *pos)
{
  if (!param       || !param->data ||
      !param->next || !param->next->data)
    return (0);
  pos->x = atoi((char *)param->data);
  pos->y = atoi((char *)param->next->data);
  circular(&c->servptr->map, pos);
  return (1);
}

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
get_tile(t_cli *c, t_node *param)
{
  t_coord	pos;
  t_hash	*tile;

  if (get_coords(c, param, &pos) == 0 ||
      (tile = t_map_at(&c->servptr->map, pos)) == NULL)
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

bool
bct(t_cli *c, t_msg *msg)
{
  g_i = 0;
  if (list_len(msg->params) != 2)
    {
      ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
	  __func__, c->sock.fd, c->team->name);
      ERR(RED"   invalid parameter count\n"WHITE);
      enqueue_msg(c, "bct : invalid parameters\n");
    }
  else
    {
      get_tile(c, msg->params->first);
      return (true);
    }
  return (true);
}
