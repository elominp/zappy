/*
** hash.h for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:32:58 2016 querat_g
** Last update Sun Jun 12 17:45:17 2016 querat_g
*/

#ifndef HASH_H_
# define HASH_H_

#include <stdlib.h>
#include "list.h"

typedef struct  s_entry
{
  void          *data;
  void          *key;
  size_t        key_size;
  size_t	hash;
}               t_entry;

typedef struct  s_hash
{
  size_t        size;
  t_list        **buckets;
  size_t        (*hash)(void const *data, size_t size);
}               t_hash;

t_hash          *ht_init(size_t size);
int             ht_add_entry(t_hash *hash,
			     void *data,
			     void const *key,
			     size_t key_size);
void            *ht_get_entry(t_hash *hash, void const *key, size_t key_size);
int             ht_rm_entry(t_hash *hash, void const *key, size_t key_size,
                            void (*destructor)(void*));
void            ht_print(t_hash *hash, void (*print)(void*));
t_hash          *ht_free(t_hash *hash, void (*ptr)(void*));
size_t          ht_count(t_hash *hash);
size_t          ht_count_if(t_hash *hash, int (*if_function)(void*));
size_t          ht_foreach(t_hash *hash, void (*func)(void*));

/*
** internal functions ------------------------------------------------------
*/
size_t          ht_hash_function(void const *data, size_t size);
int             ht_key_cmp(void const *cmp_, size_t cmp_size,
                           void const *key_, size_t key_size);
t_entry         *ht_free_entry(t_entry *entry, void (*ptr)(void*));

#endif /* !hash.h */
