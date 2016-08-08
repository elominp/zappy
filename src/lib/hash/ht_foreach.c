/*
** ht_foreach.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:28 2016 querat_g
** Last update Sat May 21 17:57:50 2016 querat_g
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"

size_t          processbucket(t_node *cur, void (*func)(void*))
{
  size_t        affected;
  t_node        *next;
  t_entry       *entry;

  affected = 0;
  while (cur)
    {
      next = cur->next;
      if (func != NULL && (entry = cur->data) != NULL && entry->data)
        {
          (func)(entry->data);
          ++affected;
        }
      cur = next;
    }

  return (affected);
}

size_t          ht_foreach(t_hash *hash, void (*func)(void*))
{
  size_t        i;
  t_node        *node;
  size_t        affected;

  i = -1;
  affected = 0;
  if (hash == NULL || hash->buckets == NULL || hash->buckets[0] == NULL)
    return (false);
  while (hash->buckets[++i] != NULL)
    affected += processbucket(node = hash->buckets[i]->first, func);
  return (affected);
}
