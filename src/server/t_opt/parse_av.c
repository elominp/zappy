/*
** parse_av.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Jun 10 11:30:26 2016 querat_g
** Last update Thu Jun 23 16:04:30 2016 querat_g
*/

#include "server.h"

static t_optcor         g_optcor[] =
  {
    {.character = 'p', NULL},
    {.character = 'x', NULL},
    {.character = 'y', NULL},
    {.character = 'n', NULL},
    {.character = 'c', NULL},
    {.character = 't', NULL},
    {.character =  0 , NULL}
  };

static void
init_optcor_tab(t_opt *o)
{
  if (!o)
    return ;
  g_optcor[0].opttoaffect = &o->port;
  g_optcor[1].opttoaffect = &o->x_size;
  g_optcor[2].opttoaffect = &o->y_size;
  (void)g_optcor[3];
  g_optcor[4].opttoaffect = &o->max_clients;
  g_optcor[5].opttoaffect = &o->time;
}

static bool
is_numeric(char *str)
{
  if (!str)
    return (false);
  while (*str)
    {
      if (*str < '0' || *str > '9')
        return (false);
      ++str;
    }
  return (true);
}

static int  init_team(void *ptr_team, void *ptr_max)
{
  t_team    *team;
  uint64_t  max;

  if ((team = ptr_team) == NULL || ptr_max == NULL)
    return (false);
  max = *((uint64_t *)ptr_max);
  team->nb_slots = max;
  return (true);
}

static bool
get_n_opt(t_opt *o, int ac, char **av)
{
  size_t        i;
  t_team        *team;

  i = optind - 1;
  if (av[i][0] == '-')
    av[i] += 2;
  for (;i < (size_t)ac && *av[i] != '-'; ++i)
    {
      if (!is_in_list(o->teams, av[i]))
        {
          if (!(team = new_t_team(av[i])))
            return (TRACE(RED"new_t_team() failed !"WHITE), false);
          if (!list_append(&o->teams, team))
            return (TRACE("list_append() failed"), delete_t_team(team),
                    false);
        }
    }
  optind = i - 1;
  o->teams->for_each(o->teams, init_team, &(o->max_clients));
  return (true);
}

bool
parse_av(t_opt *o, int ac, char **av)
{
  int           c;
  int64_t       num;
  int           i;

  init_optcor_tab(o);
  while ((c = getopt(ac, av, COMMAND_LINE_OPTS)) != -1)
    {
      if (c == '?' || !optarg || optarg[0] == '\0')
        return (usage(av), false);
      if (c != 'n' && !is_numeric(optarg))
        return (ERR("not a number %s\n", optarg), false);;
      if (c == 'n')
	{
	  if (!strncmp("-", optarg, 1))
	    return (usage(av), false);
	  get_n_opt(o, ac, av);
	}
      num = atol(optarg);
      if (num < 0)
        return (usage(av), false);
      for (i = 0; g_optcor[i].character; ++i)
        if (c == g_optcor[i].character && g_optcor[i].opttoaffect)
          *g_optcor[i].opttoaffect = num;
    }
  return (true);
}
