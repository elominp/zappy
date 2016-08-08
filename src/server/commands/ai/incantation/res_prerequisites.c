/*
** res_prerequisites.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Jun 22 09:55:22 2016 querat_g
** Last update Thu Jun 23 16:07:55 2016 querat_g
*/

#include "zappy.h"
#include "server.h"

/*
** the coding "norm" of epitech sure makes thoses comments
** 'pretty' to look at ...
**
** g_prerequisite[$(RESSOURCE)][$(LEVEL)]
*/
static int const        g_prerequisites[8][8] =
  {
    /*
    **
    ** Levels, from X to X + 1
    **
    ** XX 01 02 03 04 05 06 07
    ** |  |  |  |  |  |  |  |
    ** \/ \/ \/ \/ \/ \/ \/ \/
    ** XX 02 03 04 05 06 07 08
    */

    /*
    ** JOUEURS
    */
    { -1, 1, 2, 2, 4, 4, 6, 6 },
    /*
    ** LINEMATE
    */
    { -1, 1, 1, 2, 1, 1, 1, 2 },
    /*
    ** DERAUMERE
    */
    { -1, 0, 1, 0, 1, 2, 2, 2 },
    /*
    ** SIBUR
    */
    { -1, 0, 1, 1, 2, 1, 3, 2 },
    /*
    ** MENDIANE
    */
    { -1, 0, 0, 0, 0, 3, 0, 2 },
    /*
    ** PHIRAS
    */
    { -1, 0, 0, 2, 1, 0, 1, 2 },
    /*
    ** THYSTAME
    */
    { -1, 0, 0, 0, 0, 0, 0, 1 }
  };

int
remove_incantation_ressources_from_map(t_serv *serv, t_coord *c, int level)
{
  circular(&serv->map, c);
  t_map_take_item(&serv->map, LINEMATE, *c, g_prerequisites[LINEMATE][level]);
  t_map_take_item(&serv->map, DERAUMERE,
                  *c, g_prerequisites[DERAUMERE][level]);
  t_map_take_item(&serv->map, SIBUR, *c, g_prerequisites[SIBUR][level]);
  t_map_take_item(&serv->map, MENDIANE, *c, g_prerequisites[MENDIANE][level]);
  t_map_take_item(&serv->map, PHIRAS, *c, g_prerequisites[PHIRAS][level]);
  t_map_take_item(&serv->map, THYSTAME, *c, g_prerequisites[THYSTAME][level]);
  return (0);
}

static int
count_res(t_hash *tile, char const *ressource)
{
  t_item        *itemstack;

  if (!tile
      || !ressource
      || !(itemstack = ht_get_entry(tile, ressource, strlen(ressource))))
    {
      ERR(BROWN"res: '%s' ; count:0\n"WHITE, ressource);
      return (0);
    }
  ERR(BROWN"res: '%s' ; count:%zu\n"WHITE, ressource, itemstack->amount);
  return (itemstack->amount);
}

#ifdef __DEBUG__
static void
debug_log(t_hash *tile, int level, t_coord *c, t_serv *s)
{
  ERR(BLUE"PREREQUISITES: %d %d %d %d %d %d %d\n"WHITE,
      g_prerequisites[JOUEUR   ][level],
      g_prerequisites[LINEMATE ][level],
      g_prerequisites[DERAUMERE][level],
      g_prerequisites[SIBUR    ][level],
      g_prerequisites[MENDIANE ][level],
      g_prerequisites[PHIRAS   ][level],
      g_prerequisites[THYSTAME ][level]);
  ERR(GREEN"GIVEN:         %d %d %d %d %d %d %d\n"WHITE,
      count_players_at(s, c, level),
      count_res(tile, "linemate"),
      count_res(tile, "deraumere"),
      count_res(tile, "sibur"),
      count_res(tile, "mendiane"),
      count_res(tile, "phiras"),
      count_res(tile, "thystame"));
}
#endif

bool
tile_meets_prerequisites(t_serv *s, t_coord c, int level)
{
  t_hash        *tile;

  ASSERT(level < 8);
  circular(&s->map, &c);
  if (!(tile = t_map_at(&s->map, c)))
    return (ERR("wrong\n"), false);

#ifdef __DEBUG__
  debug_log(tile, level, &c, s);
#endif

  if (count_players_at(s, &c, level) < g_prerequisites[JOUEUR   ][level] ||
      count_res(tile, "linemate")    < g_prerequisites[LINEMATE ][level] ||
      count_res(tile, "deraumere")   < g_prerequisites[DERAUMERE][level] ||
      count_res(tile, "sibur")       < g_prerequisites[SIBUR    ][level] ||
      count_res(tile, "mendiane")    < g_prerequisites[MENDIANE ][level] ||
      count_res(tile, "phiras")      < g_prerequisites[PHIRAS   ][level] ||
      count_res(tile, "thystame")    < g_prerequisites[THYSTAME ][level])
    {
      TRACE(RED"incantation prerequisites KO !"WHITE);
      return (false);
    }
  TRACE(GREEN"incantation prerequisites OK !"WHITE);
  return (true);
}
