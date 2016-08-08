/*
** offset.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 14:05:05 2016 querat_g
** Last update Wed Jun  8 17:54:30 2016 querat_g
*/

#include <string.h>
#include <stdlib.h>
#include "myirc.h"

/*
** offset to the next space (not a \t)
*/
int
to_space(char *str)
{
  int   i;

  i = 0;
  while (str[i] && str[i] != ' ')
    ++i;
  return (i);
}

void
skip_one_space(char **str)
{
  if (str && *str && **str == ' ')
    ++(*str);
}

/*
** offset to \n or end of string
*/
int
to_crlf(char *str)
{
  int   i;

  i = 0;
  while (str[i] && strncmp(&str[i], "\n", 1))
    ++i;
  return (i);
}
