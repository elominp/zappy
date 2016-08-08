/*
** upgrade_players.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Jun 22 16:44:07 2016 querat_g
** Last update Sat Jun 25 16:47:31 2016 querat_g
*/

#include "server.h"

static t_coord  g_coord         = { 0, 0 };
static int      g_level         = -1;
static t_map    *g_map          = NULL;

static void
servclient_as_client(void *voidclient)
{
  t_cli         *c;
  t_coord       co;
  char          buffer[128];

  if (!(c = voidclient) || c->is_graphic)
    return ;
  co.x = c->x_pos;
  co.y = c->y_pos;
  circular(g_map, &co);
  if (g_coord.x == co.x && g_coord.y == co.y && c->level == g_level &&
      !c->is_graphic)
    {
      ++c->level;
      TRACE(DGREEN"client %d is now level %d"WHITE, c->sock.fd, c->level);
      snprintf(buffer, sizeof(buffer), "niveau actuel : %d\n", c->level);
      enqueue_msg(c, buffer);
      if (c->level == 8)
        {
          printf(GREEN"Team %s won the game !\n"WHITE,
               (c->team && c->team->name)
               ? c->team->name : PINK"NULL"WHITE);
          seg(c);
          c->servptr->exit = true;
        }
    }
}

int
upgrade_players_at(t_serv *s, t_coord *c, int level)
{
  g_level = level;
  g_map = &s->map;
  memcpy(&g_coord, c, sizeof(*c));
  ht_foreach(s->clients, &servclient_as_client);
  return (0);
}

static void
servclient_as_client_same_level(void *voidclient)
{
  t_cli         *c;
  t_coord       co;
  char          buffer[128];

  if (!(c = voidclient))
    return ;
  co.x = c->x_pos;
  co.y = c->y_pos;
  circular(g_map, &co);
  if (g_coord.x == co.x && g_coord.y == co.y && c->level == g_level &&
      !c->is_graphic)
    {
      TRACE(DRED"client %d stayed at same  level %d%s"WHITE,
            c->sock.fd, c->level, c->is_graphic ? "(graphic client :p)" : "");
      snprintf(buffer, sizeof(buffer), "niveau actuel : %d\n", c->level);
      enqueue_msg(c, buffer);
    }
}

int
same_level_at(t_serv *s, t_coord *c, int level)
{
  g_level = level;
  g_map = &s->map;
  memcpy(&g_coord, c, sizeof(*c));
  ht_foreach(s->clients, &servclient_as_client_same_level);
  return (0);
}
