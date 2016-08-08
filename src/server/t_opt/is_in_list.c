/*
** is_in_list.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/t_opt
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 09:30:41 2016 querat_g
** Last update Mon Jun 13 16:02:29 2016 querat_g
*/

#include "server.h"

bool
is_in_list(t_list *l, char *str)
{
  t_node        *cur;

  cur = l->first;
  while (cur)
    {
      if (!strcmp(((t_team*)cur->data)->name, str))
        return (true);
      cur = cur->next;
    }
  return (false);
}
