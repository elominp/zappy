/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Tue Jun 21 10:40:34 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static char buff[512];

static void send_to_graph_client(void *c)
{
  t_cli *client;

  client = (t_cli *)c;
  if (client->is_graphic)
    enqueue_msg(client, buff);
}

bool
pbc(t_cli *c, char const *msg)
{
  int	i;

  i = snprintf(buff, 32, "pbc %d ", c->sock.fd);
  strncpy(buff + i, msg, 510 - i);
  snprintf(buff + strlen(buff), 2, "\n");
  ht_foreach(c->servptr->clients, &send_to_graph_client);
  return (true);
}
