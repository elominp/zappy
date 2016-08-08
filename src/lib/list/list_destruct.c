/*
** list_destruct.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/lib
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 17 11:14:35 2016 querat_g
** Last update Wed May 11 15:42:40 2016 querat_g
*/

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void		list_destruct(struct s_list **this, void (*destructor)(void*))
{
  t_node	*cur;
  t_node	*prev;

  prev = NULL;
  if ((*this) == NULL)
    return ;
  if ((*this)->first == NULL)
    {
      free((*this));
      return ;
    }
  cur = (*this)->first;
  while (cur)
    {
      if (cur->data && destructor)
        (destructor)(cur->data);
      prev = cur;
      cur = cur->next;
      free(prev);
    }
  free((*this));
  (*this) = NULL;
  return ;
}
