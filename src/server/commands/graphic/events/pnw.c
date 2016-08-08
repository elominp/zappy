/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Fri Jun 24 13:56:02 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static char g_buff[512];

static void send_to_graph_client(void *c)
{
  t_cli *client;

  client = (t_cli *)c;
  if (client->is_graphic)
    enqueue_msg(client, g_buff);
}

bool
pnw(t_cli *c)
{
  if (!c->team || !c->team->name || !strcmp(c->team->name, "GRAPHIC"))
    return (false);

  snprintf(g_buff, 512, "pnw %d %ld %ld %d %d %s\n",
	   c->sock.fd,
	   c->x_pos,
	   c->y_pos,
	   c->direction,
	   c->level,
	   c->team->name);
  ht_foreach(c->servptr->clients, &send_to_graph_client);
  return (true);
}
