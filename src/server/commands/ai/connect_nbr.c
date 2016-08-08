/*
** connect_nbr.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:25:06 2016 querat_g
** Last update Mon Jun 20 17:39:33 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static bool
send_number(t_cli *c, t_team const *team)
{
  char          buffer[64];
  uint32_t      nb;

  nb = (c->servptr->opt->max_clients - team->nb_members);

  *buffer = '\0';
  if (snprintf(buffer, sizeof(buffer), "%u\n", nb) == -1)
    return (perror("snprintf()"), false);

  enqueue_msg(c, buffer);

  return (true);
}

bool
connect_nbr(t_cli *c, t_msg UNUSED(*msg))
{
  t_node        *cur;
  t_team const  *team;

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);

  if (!c->team->name || !(cur = LIST_FIRST_NODE(c->servptr->teams)))
    return (ERR(RED"no team, client %d\n"WHITE, c->sock.fd), false);

  while (cur)
    {

      if ((team = cur->data)
          && team->name
          && !strcmp(c->team->name, team->name))
        {
          send_number(c, team);
          return (true);
        }
      cur = cur->next;
    }

  return (false);
}
