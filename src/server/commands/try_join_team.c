/*
** try_join_team.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 10:32:37 2016 querat_g
** Last update Sat Jun 25 16:45:24 2016 querat_g
*/

#include "server.h"
#include "macros.h"
#include "gr_commands.h"
#include "try_join_team_static.c"

static void
send_welcome_messages(t_cli *c)
{
  char          buffer[128];

  snprintf(buffer, sizeof(buffer), "%d\n", c->sock.fd);
  enqueue_msg(c, buffer);
  snprintf(buffer, sizeof(buffer), "%ld %ld\n",
           c->servptr->map.width,
           c->servptr->map.height);
  enqueue_msg(c, buffer);
}

static bool
try_join_team_body(t_team *curteam, t_cli *c, const char *team)
{
  try_join_team_egg(curteam, c);
  ERR(GREEN"Client %d joined %s\n"WHITE, c->sock.fd, team);
  c->is_graphic = strcmp(team, GRAPHIC_TEAM_NAME) ? false : true;
  c->team = curteam;
  ++curteam->nb_members;
  if (c->is_graphic)
    try_join_team_graphic(c, NULL, NULL);
  else
    {
      send_welcome_messages(c);
      pnw(c);
    }
  return (true);
}

bool
try_join_team(t_cli *c, char const *team)
{
  t_node        *cur;
  t_team        *curteam;

  if (!c || !team || c->team || !c->servptr || !c->servptr->teams ||
      (!(cur = c->servptr->teams->first)))
    return (kick_client(c->servptr, c->sock.fd), false);
  while (cur)
    {
      if ((curteam = cur->data) && (!strcmp(team, curteam->name)))
        {
          if ((curteam->nb_members < curteam->nb_slots) ||
              (!strcmp(team, GRAPHIC_TEAM_NAME)))
            return (try_join_team_body(curteam, c, team));
          return (false);
        }
      cur = cur->next;
    }
  return (false);
}
