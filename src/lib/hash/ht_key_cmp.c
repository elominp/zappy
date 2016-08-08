/*
** ht_key_cmp.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:42 2016 querat_g
** Last update Sat Jun 11 14:22:46 2016 querat_g
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"
#include "macros.h"

int             ht_key_cmp(void const *cmp_, size_t cmp_size,
                           void const *key_, size_t key_size)
{
  size_t	i;
  char const	*cmp;
  char const	*key;

  cmp = cmp_;
  key = key_;
  i = -1;
  if (key_size > cmp_size || cmp == NULL || key == NULL)
    return (false);
  while (++i < cmp_size)
    {
      if (cmp[i] != key[i])
	return (false);
    }
  return (true);
}
