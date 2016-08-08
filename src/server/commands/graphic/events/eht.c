/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Sun Jun 26 12:20:01 2016 schmou_a
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
eht(t_cli *c)
{
  t_egg *egg;

  if (!c->team)
    return (false);
  if (c->team && c->team->name && !strcmp(c->team->name, "GRAPHIC"))
    return (false);
  egg = c->
    team->
    eggs_sorted->
    first->data;
  snprintf(g_buff, 50, "eht %lu\n", egg->id);
  ht_foreach(c->servptr->clients, &send_to_graph_client);
  return (true);
}
