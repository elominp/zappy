/*
** pgt.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Jun 26 14:45:21 2016 querat_g
** Last update Sun Jun 26 14:45:22 2016 querat_g
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
  if (client && client->is_graphic)
    enqueue_msg(client, g_buff);
}

bool
pgt(t_cli *c, t_rsrc taken_ressource)
{
  DEBUG("pgt()");
  snprintf(g_buff, sizeof(g_buff),
           "pgt %d %d\n", c->sock.fd, taken_ressource);
  ht_foreach(c->servptr->clients, &send_to_graph_client);
  return (true);
}
