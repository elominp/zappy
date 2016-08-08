/*
** incantation.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:21:07 2016 querat_g
** Last update Sun Jun 26 11:01:57 2016 schmou_a
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

bool
incantation(t_cli *c, t_msg UNUSED(*msg))
{

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);

  if (c->level > 7)
    return (false);

  if (!tile_meets_prerequisites((c->servptr),
                                (t_coord){ c->x_pos, c->y_pos },
                                (c->level)))
    return (pie(c, 0), same_level_at(c->servptr,
                                     &(t_coord){c->x_pos, c->y_pos},
                                     c->level), false);

  remove_incantation_ressources_from_map(c->servptr,
                                         &(t_coord){ c->x_pos, c->y_pos },
                                         c->level);
  upgrade_players_at(c->servptr, &(t_coord){c->x_pos, c->y_pos}, c->level);
  pie(c, 1);
  if (c->level == 8)
    seg(c);
  return (true);
}
