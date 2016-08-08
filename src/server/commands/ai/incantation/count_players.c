/*
** count_players.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Jun 22 12:32:30 2016 querat_g
** Last update Wed Jun 22 16:51:11 2016 querat_g
*/

#include "server.h"

static int      g_player_count  = 0;
static t_coord  g_coord         = { 0, 0 };
static int      g_level         = -1;
static t_map    *g_map          = NULL;

static void
servclient_as_client(void *voidclient)
{
  t_cli         *c;
  t_coord       co;

  if (!(c = voidclient))
    return ;
  co.x = c->x_pos;
  co.y = c->y_pos;
  circular(g_map, &co);

  if (g_coord.x == co.x && g_coord.y == co.y &&
      c->level == g_level && !c->is_graphic)
    ++g_player_count;
}

int
count_players_at(t_serv *s, t_coord *c, int level)
{
  g_level = level;
  g_map = &s->map;
  g_player_count = 0;
  memcpy(&g_coord, c, sizeof(*c));
  ht_foreach(s->clients, &servclient_as_client);
  return (g_player_count);
}
