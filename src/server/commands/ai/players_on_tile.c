/*
** players_on_tile.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Jun 15 09:44:04 2016 querat_g
** Last update Wed Jun 22 15:16:52 2016 querat_g
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "macros.h"

static int      g_count = 0;
static t_coord  g_pos   = { 0, 0 };

static void
count_players(void *clidata)
{
  t_cli         *cli;

  if (!(cli = clidata))
    return ;

  if (cli->x_pos == g_pos.x && cli->y_pos == g_pos.y)
    ++g_count;
}

int
count_players_on_tile(t_cli *c, t_coord pos)
{
  g_count = 0;
  g_pos.x = pos.x % c->servptr->map.width;
  g_pos.y = pos.y % c->servptr->map.height;

  ht_foreach(c->servptr->clients, &count_players);

  return (g_count);
}
