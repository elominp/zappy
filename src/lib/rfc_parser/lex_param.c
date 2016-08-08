/*
** lex_param.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 15:18:47 2016 querat_g
** Last update Sun May 29 15:21:27 2016 querat_g
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "macros.h"
#include "myirc.h"

/*
** <param> ::= <SPACE> [ ’:’ <trailing> | <middle> <params> ]
*/
bool
lex_param(t_list **params, char **str)
{
  char  *res;
  int   offset;

  skip_one_space(str);
  if (**str == ':')
    {
      ++(*str);
      offset = to_crlf(*str);
      res = strndup(*str, offset);
      (*str) += offset;
      if (!res || !((*params)->append(params, res)))
        return (TRACE("list_append() failed"), free(res), false);
    }
  else
    {
      offset = to_space(*str);
      if (!(res = strndup(*str, offset)))
        return (TRACE("strndup(): %s", strerror(errno)));
      if (!((*params)->append(params, res)))
        return (TRACE("list_append() failed"), free(res), false);
      *str += offset;
    }
  return (true);
}
