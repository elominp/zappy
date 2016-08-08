/*
** ht_rm_entry.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:48 2016 querat_g
** Last update Sun Jun 12 14:17:26 2016 querat_g
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"

int             ht_rm_entry(t_hash *hash,
			    void const *key,
			    size_t key_size,
                            void (*destructor)(void*))
{
  int           offset;
  t_list	*list;
  t_node	*node;
  t_entry       *entry;
  size_t        i;

  entry = NULL;
  offset = (hash->hash(key, key_size) % hash->size);
  if (((list = (hash->buckets[offset])) == NULL) ||
      ((node = list->first) == NULL))
    return (false);
  i = 0;
  while (node != NULL)
    {
      entry = node->data;
      if (entry != NULL)
        if (ht_key_cmp(key, key_size, entry->key, entry->key_size))
          {
            ht_free_entry(entry, destructor);
            return (list->rm_node(list, i, NULL), true);
          }
      i++;
      node = node->next;
    }
  return (false);
}
