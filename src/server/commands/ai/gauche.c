/*
** gauche.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Jun 26 14:45:47 2016 querat_g
** Last update Sun Jun 26 14:45:48 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

extern char const       *g_direction_str[];
char                    g_buffer[128];

static void
servclient_as_client(void *clivoid)
{
  t_cli         *cli;

  if (!(cli = clivoid))
    return ;

  if (cli->is_graphic)
    enqueue_msg(cli, g_buffer);
}

bool
send_ppo(t_cli *c)
{
  snprintf(g_buffer, sizeof(g_buffer), "ppo %d %ld %ld %d\n",
           c->sock.fd,
           c->x_pos,
           c->y_pos,
           to_graphical_dir(c->direction));

  ht_foreach(c->servptr->clients, &servclient_as_client);

  return (true);
}

bool
gauche(t_cli *c, t_msg UNUSED(*msg))
{
  static const enum e_dir g_to[] =
    {
      LEFT,
      RIGHT,
      DOWN,
      UP
    };

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);

  c->direction = g_to[c->direction % 4];
  ERR("new direction: "GREEN"'%s'"WHITE"\n",
      g_direction_str[c->direction % 4]);
  enqueue_msg(c, "ok\n");
  send_ppo(c);
  return (true);
}
