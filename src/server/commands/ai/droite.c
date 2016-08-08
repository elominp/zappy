/*
** droite.c<2> for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:13:31 2016 querat_g
** Last update Fri Jun 24 17:09:47 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

char const                      *g_direction_str[] =
  {
    "UP",
    "DOWN",
    "LEFT",
    "RIGHT"
  };

char const
*get_direction_str(enum e_dir direction)
{
  return (g_direction_str[direction]);
}

bool
droite(t_cli *c, t_msg UNUSED(*msg))
{
  static const enum e_dir       g_to[] =
    {
      RIGHT,
      LEFT,
      UP,
      DOWN
    };

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);

  c->direction = g_to[c->direction];
  ERR("new direction: "GREEN"'%s'"WHITE"\n",
      g_direction_str[c->direction]);
  enqueue_msg(c, "ok\n");
  send_ppo(c);
  return (true);
}
