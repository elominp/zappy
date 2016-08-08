/*
** list_cmp.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Feb 25 11:07:03 2016 querat_g
** Last update Thu Feb 25 14:19:43 2016 querat_g
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

static void	swap(void **p1, void **p2)
{
  void		*swap;

  swap = (*p1);
  (*p1) = (*p2);
  (*p2) = swap;
}

int		list_sort(t_list *this, int (*cmp)(void *p1, void *p2))
{
  t_node	*cur;
  t_node	*prev;
  int		act;

  if (!this || !this->first || !cmp)
    return (0);
  act = false;
  cur = this->first;
  while ((cur))
    {
      prev = cur;
      cur = cur->next;
      if (cur && prev && prev != cur)
	{
	  if ((cmp)(prev->data, cur->data) > 0)
	    {
	      swap(&cur->data, &prev->data);
	      act = true;
	    }
	}
    }
  return (act ? list_sort(this, cmp) : false);
}
