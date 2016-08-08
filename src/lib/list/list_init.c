/*
** list_init.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/lib
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 17 11:14:49 2016 querat_g
** Last update Sun May 29 18:24:43 2016 querat_g
*/

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

/*
** Pseudo-constructeur de liste chaînée
*/
t_list		*new_list()
{
  t_list	*this;

  this = malloc(sizeof(t_list));
  if (this == NULL)
    return (NULL);
  this->first = NULL;
  this->last = NULL;
  this->append = &list_append;
  this->prepend = &list_prepend;
  this->destruct = &list_destruct;
  this->print = &list_print;
  this->rm_node = &list_rm_node;
  this->rm_first_node = &list_rm_first_node;
  this->rm_last_node = &list_rm_last_node;
  this->insert = &list_insert;
  this->sort = &list_sort;
  this->for_each = &list_for_each;
  this->remove_if = &list_remove_if;
  this->count_if = &list_count_if;

  return (this);
}
