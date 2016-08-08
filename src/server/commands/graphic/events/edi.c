/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
** 
** Made by schmou_a
** Login   <schmou@epitech.net>
** 
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 16 16:58:15 2016 schmou_a
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
edi(t_hash *clients, t_egg *egg)
{
  snprintf(g_buff, 50, "edi %lu\n", egg->id);
  ht_foreach(clients, &send_to_graph_client);
  return (true);
}
