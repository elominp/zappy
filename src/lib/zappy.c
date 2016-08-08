/*
** zappy.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/t_opt
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 11:15:01 2016 querat_g
** Last update Wed Jun 15 16:55:07 2016 querat_g
*/

#include <stdlib.h>
#include <string.h>
#include "zappy.h"
#include "macros.h"

const struct s_rsrc_to_string  g_rsrc_to_string[] =
  {
    {NOURRITURE   , "nourriture"},
    {LINEMATE     , "linemate"  },
    {DERAUMERE    , "deraumere" },
    {SIBUR        , "sibur"     },
    {MENDIANE     , "mendiane"  },
    {PHIRAS       , "phiras"    },
    {THYSTAME     , "thystame"  },
    {INVALID      , NULL        }
  };

char const
*get_rsrc_string_from_enum(enum e_rsrc res)
{
  size_t        i;

  i = 0;
  while (g_rsrc_to_string[i].enumeration != INVALID &&
         g_rsrc_to_string[i].string)
    {
      if (g_rsrc_to_string[i].enumeration == res)
        return (g_rsrc_to_string[i].string);
      ++i;
    }
  return (g_rsrc_to_string[i].string);
}

enum e_rsrc
get_rsrc_enum_from_string(char const *str)
{
  size_t        i;

  i = 0;
  if (!str)
    return (INVALID);

  while ((g_rsrc_to_string[i].enumeration != INVALID) &&
         (g_rsrc_to_string[i].string))
    {
      if (!strcasecmp(str, g_rsrc_to_string[i].string))
        return (g_rsrc_to_string[i].enumeration);
      ++i;
    }
  return (INVALID);
}
