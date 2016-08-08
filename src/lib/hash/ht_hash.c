/*
** ht_hash.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:30:37 2016 querat_g
** Last update Sat Jun 11 16:49:35 2016 querat_g
*/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "hash.h"
#include "macros.h"

size_t          ht_hash_function(void const *data, size_t size)
{
  size_t        i;
  char const    *str;
  size_t        sum;

  str = data;
  if (str == NULL)
    return (0);
  i = 0;
  sum = 1;
  while (i < size)
    {
      sum *= str[i];
      if (i > 0)
        sum ^= str[i - 1];
      ++i;
    }
  return (sum);
}
