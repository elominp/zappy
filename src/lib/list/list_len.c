/*
** list_len.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/lib
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 17 11:13:46 2016 querat_g
** Last update Wed Feb 17 11:14:00 2016 querat_g
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

int		list_len(struct s_list *this)
{
  int		i;
  t_node	*cur;

  if (this->first == NULL)
    return (0);
  i = 1;
  cur = this->first;
  while ((cur = cur->next))
    ++i;
  return (i);
}
