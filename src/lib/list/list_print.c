/*
** list_print.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/lib
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 17 11:13:28 2016 querat_g
** Last update Wed Feb 17 11:13:36 2016 querat_g
*/

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void		list_print(t_list *this, void (*printer)(void*))
{
  t_node	*current_node;

  if (this == NULL || this->first == NULL)
    return ;
  current_node = this->first;
  while (current_node != NULL)
    {
      if (current_node->data != NULL)
        (printer)(current_node->data);
      current_node = current_node->next;
    }
  return ;
}
