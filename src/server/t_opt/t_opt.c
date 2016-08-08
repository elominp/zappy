/*
** t_opt.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Jun 10 09:59:44 2016 querat_g
** Last update Sat Jun 25 11:30:52 2016 querat_g
*/

#include "server.h"

bool
t_opt_dest(t_opt *o)
{
  if (!o)
    return (false);
  if (o->teams)
    list_destruct(&o->teams, &delete_t_team);
  ZERO_MEM(o);
  return (false);
}

static bool
insert_graphic_team(t_list **teamlist)
{
  t_team        *team;

  if (!(team = new_t_team(GRAPHIC_TEAM_NAME)))
    return (TRACE("new_t_team() failed !"), false);
  if (!list_append(teamlist, team))
    return (TRACE("list_append() failed !"), delete_t_team(team), false);
  return (true);
}

static bool
opts_are_valid(t_opt *o)
{
  if ((o->x_size * o->y_size) > MAX_TILE_NUMBER)
    {
      ERR(RED"Requested map size must be < %d  total"WHITE, MAX_TILE_NUMBER);
      return (false);
    }
  if (o->time > 1000)
    return (ERR(RED"-t opt must be < 1000\n"WHITE), false);
  if (list_len(o->teams) < 2)
    return (ERR(RED"need a team, add one or more with -n !\n"WHITE), false);
  if (o->port >= 0xFFFF || !o->port)
    return (ERR(RED"You need to define a port number (-p)\n"WHITE), false);
  if (o->port > 0xFFFF)
    return (ERR(RED"Port number should be < 65536\n"WHITE), false);
  return (true);
}

static int
assign_max_clients_nb(void *teamvoid, void *max)
{
  if (teamvoid && max)
    ((t_team*)teamvoid)->nb_slots = *(uint64_t*)max;
  return (0);
}

bool
t_opt_const(t_opt *o, int ac, char **av)
{
  ZERO_MEM(o);
  if (ac < 2)
    return (usage(av), false);
  o->teams = new_list();
  if (!o->teams)
    return (TRACE("new_list() failed"), t_opt_dest(o), false);
  if (!parse_av(o, ac, av))
    return (t_opt_dest(o), false);
  if (!(is_in_list(o->teams, GRAPHIC_TEAM_NAME)) &&
      !(insert_graphic_team(&o->teams)))
    return (t_opt_dest(o), false);

  o->x_size = (o->x_size > 10) ? o->x_size : 20;
  o->y_size = (o->y_size > 10) ? o->y_size : 20;
  o->max_clients = o->max_clients ? o->max_clients : 10;
  o->time = o->time ? o->time : 100;

  if (!opts_are_valid(o))
    return (usage(av), t_opt_dest(o), false);
  list_for_each(o->teams, &assign_max_clients_nb, &o->max_clients);
  return (true);
}
