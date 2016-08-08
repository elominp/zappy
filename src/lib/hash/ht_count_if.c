/*
** ht_count_if.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 18:26:24 2016 querat_g
** Last update Sun May 29 18:55:33 2016 querat_g
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"

size_t          ht_count_if(t_hash *hash, int (*if_function)(void*))
{
  size_t        size;
  size_t        i;
  t_node        *node;
  t_entry       *entry;

  size = 0;
  i = -1;
  if (!hash || !hash->buckets || !hash->buckets[0] || !if_function)
    return (0);
  while ((hash->buckets[++i]))
    {
      node = hash->buckets[i]->first;
      {
        while (node)
          {
            if ((entry = node->data) && entry->data &&
                if_function(entry->data))
              ++size;
            node = node->next;
          }
      }
    }
  return (size);
}
