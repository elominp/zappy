/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Tue Jun 21 11:45:56 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static char buff[256];
static int  i = 0;

static t_cli
*get_client(t_cli *c, t_msg *msg)
{
  int	id;

  if (msg == NULL || msg->params == NULL ||
      msg->params->first == NULL || msg->params->first->data == NULL ||
      (id = atoi((char *)msg->params->first->data)) == 0)
    return (NULL);
  return ((t_cli *)ht_get_entry(c->servptr->clients, &id, sizeof(c->sock.fd)));
}

static int
get_object(t_hash *inventory, char *obj_name)
{
  t_item *it;
  int	len;

  if ((it = ht_get_entry(inventory, obj_name, strlen(obj_name))) == NULL)
    len = snprintf(buff + i, 64 - i, "0 ");
  else
    len = snprintf(buff + i, 64 - i, "%lu ", it->amount);
  return (len);
}

bool
pin(t_cli *c, t_msg *msg)
{
  t_cli	*target;
  int	id;

  if ((target = get_client(c, msg)) == NULL || target->inventory == NULL)
    return ((ERR(PINK"[%s], client %d from team '%s': client not found\n"WHITE,
		 __func__, c->sock.fd, c->team->name)), false);
  id = target->sock.fd;
  i = snprintf(buff, 64, "pin %d %ld %ld ", id, target->x_pos, target->y_pos);
  i += get_object(target->inventory, "nourriture");
  i += get_object(target->inventory, "linemate");
  i += get_object(target->inventory, "deraumere");
  i += get_object(target->inventory, "sibur");
  i += get_object(target->inventory, "mendiane");
  i += get_object(target->inventory, "phiras");
  i += get_object(target->inventory, "thystame");
  snprintf(buff + i - 1, 2, "\n");
  i = 0;
  enqueue_msg(c, buff);
  return (true);
}
