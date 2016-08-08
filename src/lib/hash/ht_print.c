/*
** ht_print.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:46 2016 querat_g
** Last update Sun Jun 12 17:55:33 2016 querat_g
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include "list.h"
#include "hash.h"
#include "macros.h"

void            ht_print(t_hash *hash, void (*print)(void*))
{
  t_list        *bucket;
  t_node        *list;
  size_t        i;

  if (hash == NULL || hash->buckets == NULL || hash->buckets[0] == NULL)
    return ;
  i = -1;
  ERR("\nDumping t_hash* hashtable --------------------------------\n");
  while (++i < hash->size)
    {
      ERR("[%p] bucket index '%zu'-------------------------------\n",
          hash->buckets[i], i);
      bucket = hash->buckets[i];
      if (bucket != NULL && bucket->first != NULL)
        {
          list = bucket->first;
          while (list != NULL)
            {
              if (list->data && print)
                (print)(((t_entry*)list->data)->data);
              list = list->next;
            }
        }
    }
  ERR("----------------------------------------------------------\n\n");
}
