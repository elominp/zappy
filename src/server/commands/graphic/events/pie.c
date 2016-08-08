/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Sat Jun 25 15:48:14 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static char g_buffer[128];
static int  g_success = 0;

static void
callback(void *voidcli)
{
  t_cli *c;

  if (!(c = voidcli) || !c->is_graphic)
    return ;
  enqueue_msg(c, g_buffer);
}

bool
pie(t_cli *c, int success)
{
  g_success = success;
  snprintf(g_buffer, sizeof(g_buffer),
           "pie %ld %ld %d\n", c->x_pos, c->y_pos, g_success);
  ht_foreach(c->servptr->clients, &callback);
  return (true);
}
