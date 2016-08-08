/*
** ht_count.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:25 2016 querat_g
** Last update Sun May 29 18:28:08 2016 querat_g
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"

size_t          ht_count(t_hash *hash)
{
  size_t        size;
  size_t        i;
  t_node        *node;

  size = 0;
  i = -1;
  if (hash == NULL || hash->buckets == NULL || hash->buckets[0] == NULL)
    return (0);
  while ((hash->buckets[++i]))
    {
      node = hash->buckets[i]->first;
      {
        while (node)
          {
            size = (node->data != NULL) ? size + 1 : size;
            node = node->next;
          }
      }
    }
  return (size);
}
