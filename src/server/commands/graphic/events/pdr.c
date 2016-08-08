/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 23 16:12:48 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static char g_buff[128];

static void send_to_graph_client(void *c)
{
  t_cli *client;

  client = (t_cli *)c;
  if (client->is_graphic)
    enqueue_msg(client, g_buff);
}

bool
pdr(t_cli *c, t_rsrc dropped_ressource)
{
  ERR(BLUE"pdr()"WHITE);
  snprintf(g_buff, sizeof(g_buff),
           "pdr %d %d\n", c->sock.fd, dropped_ressource);
  ht_foreach(c->servptr->clients, &send_to_graph_client);
  return (true);
}
