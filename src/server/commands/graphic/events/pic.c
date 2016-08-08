/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 23 16:12:32 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static   char	g_buff[1024];

static void send_to_graph_client(void *c)
{
  t_cli *client;

  client = (t_cli *)c;
  if (client->is_graphic)
    enqueue_msg(client, g_buff);
}

bool
pic(t_cli *c)
{
  snprintf(g_buff, 1024, "pic %ld %ld %d\n",
	   c->servptr->map.width,
	   c->servptr->map.height,
	   c->sock.fd);
  ht_foreach(c->servptr->clients, &send_to_graph_client);
  return (true);
}
