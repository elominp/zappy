/*
** expulse.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:19:27 2016 querat_g
** Last update Fri Jun 24 14:52:11 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static t_coord          g_coord = { 0, 0 };
static int              g_expulser_id = 0;
static enum e_dir       g_direction = UP;

static void
move_client(t_cli *c, enum e_dir direction)
{
  static t_coord        corresp[] =
    {
      { 0, -1 },
      { 0,  1 },
      {-1,  0 },
      { 1,  0 }
    };

  c->x_pos += corresp[direction].x;
  c->y_pos += corresp[direction].y;

  c->x_pos = (c->x_pos < 0)
    ? (c->servptr->map.width - 1)
    : (c->x_pos % c->servptr->map.width);
  c->y_pos = (c->y_pos < 0)
    ? (c->servptr->map.height - 1)
    : (c->y_pos % c->servptr->map.height);
}

static void
expulse_callback(void *cli_void)
{
  t_cli                 *c;
  char                  buffer[64];

  if (!(c = cli_void))
    return ;

  if (c->x_pos != g_coord.x
      || c->y_pos != g_coord.y
      || g_expulser_id == c->sock.fd
      || c->is_graphic)
    return ;

  *buffer = '\0';
  snprintf(buffer, sizeof(buffer),
           "deplacement: %s\n", get_direction_str(g_direction));

  move_client(c, g_direction);
  enqueue_msg(c, buffer);
}

bool
expulse(t_cli *c, t_msg UNUSED(*msg))
{
  g_coord.x     = c->x_pos;
  g_coord.y     = c->y_pos;
  g_expulser_id = c->sock.fd;
  g_direction   = c->direction;

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);

  if (count_players_on_tile(c, g_coord) < 2)
    {
      enqueue_msg(c, "ko\n");
      return (false);
    }

  ht_foreach(c->servptr->clients, &expulse_callback);
  enqueue_msg(c, "ok\n");
  pex(c);
  return (true);
}
