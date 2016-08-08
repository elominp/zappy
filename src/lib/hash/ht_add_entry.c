/*
** ht_add_entry.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:21 2016 querat_g
** Last update Sat Jun 11 17:37:40 2016 querat_g
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"
#include "macros.h"

static void     *duplicate_key(void const *src, size_t size)
{
  void          *ptr;

  if (!(ptr = malloc(size)))
    return (NULL);
  memcpy(ptr, src, size);
  return (ptr);
}

int             ht_add_entry(t_hash *hash, void *data,
                             void const *key, size_t key_size)
{
  size_t	hashed_key;
  size_t        offset;
  t_entry       *entry;

  hashed_key = (hash->hash)(key, key_size);
  offset = hashed_key % hash->size;
  entry = malloc(sizeof(t_entry));
  if (entry == NULL)
    return (false);
  entry->data = data;
  entry->key = duplicate_key(key, key_size);
  if (!entry->key)
    {
      free(entry);
      return (false);
    }
  entry->key_size = key_size;
  entry->hash = hashed_key;
  return ((*(hash->buckets[offset])).prepend(&hash->buckets[offset], entry));
}
