/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 23 16:12:04 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static int  g_i = 0;

static t_cli
*get_client(t_cli *c, t_msg *msg)
{
  int	id;
  t_cli *cl;

  if (msg == NULL || msg->params == NULL ||
      msg->params->first == NULL || msg->params->first->data == NULL ||
      (id = atoi((char *)msg->params->first->data)) == 0)
    return (NULL);
  cl = (t_cli *)ht_get_entry(c->servptr->clients, &id, sizeof(c->sock.fd));
  return (cl);
}

bool
plv(t_cli *c, t_msg *msg)
{
  char	buff[64];
  t_cli	*target;
  int	id;

  if ((target = get_client(c, msg)) == NULL || target->inventory == NULL)
    return ((ERR(PINK"[%s], client %d from team '%s': client not found\n"WHITE,
		 __func__, c->sock.fd, c->team->name)), false);
  memset(buff, 0, 64);
  g_i = 0;
  id = target->sock.fd;
  g_i = snprintf(buff, 16, "plv %d ", id);
  snprintf(buff + g_i, 64 - g_i, "%d\n", target->level);
  enqueue_msg(c, buff);
  return (true);
}
