/*
** populate_map.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Jun 23 09:31:34 2016 querat_g
** Last update Sat Jun 25 15:35:53 2016 querat_g
*/

#include <time.h>
#include <stdlib.h>
#include "server.h"

static float const   nb_tiles_per_bundle   = 100;
static int           g_amount_per_bundle[] =
/*
**  Nourriture, Linemate, deraumere, sibur, mendiane, phiras, thystame
*/
  { 80        , 9       , 8        , 10   , 5       , 6     , 1       };

static void
according_to_map_size(int64_t x, int64_t y)
{
  int           i;
  float         ratio;

  ratio = (x * y) / nb_tiles_per_bundle;
  ERR(BLUE"ressources spawning on map:\n"WHITE);
  for (i = 0; i < 7; ++i)
    {
      g_amount_per_bundle[i] *= ratio;
      ERR(DBLUE"%s: %d\n"WHITE,
          get_rsrc_string_from_enum(i),
          g_amount_per_bundle[i]);
    }
  ERR(BLUE"---------------------------\n"WHITE);
}

int
populate_map(t_map *m)
{
  int           i;
  int           total;

  srand(time(NULL));
  according_to_map_size(m->width, m->height);
  for (i = 0; i < 7; ++i)
    {
      for (total = 0; total < g_amount_per_bundle[i]; ++total)
        {
          t_map_add_item(m,
                         i,
                         (t_coord){rand() % m->width, rand() % m->height },
                         1);
        }
    }
  return (0);
}
