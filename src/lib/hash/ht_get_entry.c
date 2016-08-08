/*
** ht_get_entry.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:34 2016 querat_g
** Last update Tue Jun 21 11:25:23 2016 querat_g
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"
#include "macros.h"

void            *ht_get_entry(t_hash *hash, void const *key, size_t key_size)
{
  size_t        offset;
  t_entry       *entry;
  t_node	*node;
  t_list	*list;

  entry = NULL;
  offset = hash->hash(key, key_size);
  offset = (offset % hash->size);
  if (((list = (hash->buckets[offset])) == NULL) ||
      ((node = list->first) == NULL))
    return (NULL);
  while (node != NULL)
    {
      entry = node->data;
      if (entry != NULL)
	{
	  if (ht_key_cmp(key, key_size, entry->key, entry->key_size))
	    return (entry->data);
	}
      node = node->next;
    }
  return (NULL);
}
