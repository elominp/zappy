/*
** memdup.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 18:49:39 2016 querat_g
** Last update Sun May 29 18:52:09 2016 querat_g
*/

#include <string.h>
#include <stdlib.h>

void
*memdup(void *src, size_t size)
{
  char  *ret;

  if (!src || !(ret = malloc(size)))
    return (NULL);
  memcpy(ret, src, size);
  return (ret);
}
