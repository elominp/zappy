/*
** remove_if.c for  in /home/querat_g/tmp/PSU_2015_myftp/src/lib
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu May  5 11:10:15 2016 querat_g
** Last update Thu Jun  2 16:11:03 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "macros.h"

int             list_remove_if(t_list *this,
                               int (*if_function)(void*),
                               void (*rm_function)(void*))
{
  off_t         i;
  t_node        *cur;
  int           nbrm;

  nbrm = 0;
  if ((i = 0) || !this || !if_function || !rm_function || !(cur = this->first))
    return (false);
  while (cur)
    {
      if (cur->data && if_function(cur->data))
        {
          this->rm_node(this, i, rm_function);
          ++nbrm;
          cur = this->first;
          i = 0;
        }
      else
        cur = cur->next;
      ++i;
    }
  return (nbrm);
}
