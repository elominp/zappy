/*
** t_team.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon Jun 13 15:08:39 2016 querat_g
** Last update Thu Jun 23 10:55:45 2016 querat_g
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

bool
t_team_dest(t_team *t)
{
  if (t->name)
    free(t->name);

  ht_free(t->eggs, NULL);
  list_destruct(&t->eggs_sorted, NULL);
  ZERO_MEM(t);
  return (false);
}

bool
t_team_const(t_team *t, char *name)
{
  ZERO_MEM(t);
  if (!t || !name)
    return (false);
  if (!(t->name = strdup(name)))
    {
      perror("strdup()");
      t_team_dest(t);
      return (false);
    }
  if (!(t->eggs = ht_init(101)))
  {
    fprintf(stderr, "impossible to create hashtable of eggs\n");
    t_team_dest(t);
    return (false);
  }
  if (!(t->eggs_sorted = new_list()))
  {
    fprintf(stderr, "impossible to create list of eggs\n");
    t_team_dest(t);
    return (false);
  }
  return (true);
}

t_team
*new_t_team(char *name)
{
  t_team        *t;

  t = malloc(sizeof(*t));
  if (!t)
    return (perror("malloc()"), NULL);

  if (!t_team_const(t, name))
    return (free(t), NULL);

  return (t);
}

void
delete_t_team(void *team)
{
  if (!team)
    return ;

  t_team_dest(team);
  free(team);

  return ;
}
