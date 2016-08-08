/*
** list_prepend.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/lib
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 17 11:13:23 2016 querat_g
** Last update Wed Feb 17 11:13:24 2016 querat_g
*/

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int	list_prepend(struct s_list **this, void *data)
{
  t_node	*new;

  if (this == NULL || (*this) == NULL)
    return (false);
  new = malloc(sizeof(t_node));
  if (new == NULL)
    return (false);
  new->data = data;
  new->next = (*this)->first;
  (*this)->first = new;
  if ((*this)->first->next == NULL)
    (*this)->last = new;
  return (true);
}
