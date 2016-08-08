/*
** regex.c for  in /home/querat_g/tmp/test
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 28 15:06:55 2016 querat_g
** Last update Sun May 29 13:55:41 2016 querat_g
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <sys/types.h>
#include <regex.h>

#include "macros.h"
#include "list.h"
#include "my_regex.h"

int
regex_does_match(char *regstr, char *str)
{
  regex_t       reg;
  regmatch_t    match;

  if (regcomp(&reg, regstr, REG_EXTENDED))
    return (TRACE("regcomp() failed\n"), -1);
  if (regexec(&reg, str, 1, &match, 0))
    return (regfree(&reg), 0);
  regfree(&reg);
  return (1);
}

int
regex_skip_match(char *regstr, char **str)
{
  regex_t       reg;
  regmatch_t    match;

  if (regcomp(&reg, regstr, REG_EXTENDED))
    return (TRACE("regcomp() failed\n"), -1);
  if (regexec(&reg, *str, 1, &match, 0))
    return (regfree(&reg), 0);
  *str += match.rm_eo;
  regfree(&reg);
  return (1);
}

int
regex_get_match(char *regstr, char *str, char **res)
{
  regex_t       reg;
  regmatch_t    match;
  int           size;

  if (regcomp(&reg, regstr, REG_EXTENDED))
    return (TRACE("regcomp() failed"), -1);

  if (regexec(&reg, str, 1, &match, 0) || match.rm_so == -1)
    return (regfree(&reg), 0);

  size = match.rm_eo - match.rm_so;
  if (res && !(*res = strndup(&str[match.rm_so], size)))
    return (regfree(&reg), TRACE("strndup() failed"), -1);
  regfree(&reg);
  return (1);
}

int
regex_get_and_skip_match(char *regstr, char **str, char **res)
{
  regex_t       reg;
  regmatch_t    match;
  int           size;

  if (regcomp(&reg, regstr, REG_EXTENDED))
    return (TRACE("regcomp() failed"), -1);

  if (regexec(&reg, *str, 1, &match, 0) || match.rm_so == -1)
    return (regfree(&reg), 0);

  size = match.rm_eo - match.rm_so;
  if (res && !(*res = strndup(*str + match.rm_so, size)))
    return (regfree(&reg), TRACE("strndup() failed"), -1);
  *str += match.rm_eo;
  regfree(&reg);
  return (1);
}
