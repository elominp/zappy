/*
** avance.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:09:14 2016 querat_g
** Last update Sat Jun 25 16:44:37 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

/*
** Needed to orient the client
**
** UP
** DOWN
** LEFT
** RIGHT
*/
static t_coord  g_direction[] =
  {
    { 0  , -1 },
    { 0  , 1  },
    { -1 , 0  },
    { 1  , 0  }
  };

bool
avance(t_cli *c, t_msg UNUSED(*msg))
{
  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);

  c->x_pos += g_direction[c->direction].x;
  c->y_pos += g_direction[c->direction].y;

  c->x_pos = (c->x_pos < 0)
    ? (c->servptr->map.width - 1)
    : c->x_pos % c->servptr->map.width;

  c->y_pos = (c->y_pos < 0)
    ? (c->servptr->map.height - 1)
    : c->y_pos % c->servptr->map.height;

  ERR(DBLUE"new position x:%ld y:%ld\n"WHITE,
      c->x_pos, c->y_pos);
  enqueue_msg(c, "ok\n");
  send_ppo(c);
  return (true);
}
