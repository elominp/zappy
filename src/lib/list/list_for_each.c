/*
** list_for_each.c for  in /home/querat_g/tmp/PSU_2015_myftp/src/lib
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu May  5 08:54:49 2016 querat_g
** Last update Sun May 22 12:17:01 2016 querat_g
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

int             list_for_each(t_list *this,
                              int (*function)(void*, void*),
                              void *data)
{
  t_node        *cur;
  t_node        *next;

  if (!this || !(cur = this->first) || !function)
    return (false);

  while (cur)
    {
      next = cur->next;
      function(cur->data, data);
      cur = next;
    }

  return (true);
}
