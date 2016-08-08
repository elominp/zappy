/*
** list_count_if.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 18:22:20 2016 querat_g
** Last update Sun May 29 18:23:59 2016 querat_g
*/

#include "list.h"

int     list_count_if(t_list *this, int (*if_function)(void*))
{
  int           count;
  t_node        *cur;

  count = 0;
  if (!this || !(cur = this->first) || !if_function)
    return (0);

  while (cur)
    {
      if (if_function(cur->data))
        ++count;
      cur = cur->next;
    }

  return (count);
}
