/*
** fork.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:23:46 2016 querat_g
** Last update Fri Jun 24 15:05:56 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"
#include "gr_commands.h"

bool
fork_ai(t_cli *c, t_msg *msg)
{
  t_egg *egg;

  (void)msg;
  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);
  egg = calloc(1, sizeof(t_egg));
  c->servptr->prev_egg_id += 1;
  egg->id = c->servptr->prev_egg_id;
  egg->x = c->x_pos;
  egg->y = c->y_pos;
  egg->life_time = 1260;
  ht_add_entry(c->team->eggs, egg, &(egg->id), sizeof(egg->id));
  list_prepend(&(c->team->eggs_sorted), egg);
  c->team->nb_slots += 1;
  enw(c);
  enqueue_msg(c, "ok\n");
  return (true);
}
