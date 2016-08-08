/*
** voir.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:17:04 2016 querat_g
** Last update Sat Jun 25 10:41:43 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

/*
** Needed to orient the focus towards the direction the client
** is facing
**
** UP
** DOWN
** LEFT
** RIGHT
*/
static t_coord          g_coef[] =
  {
    { 1  , -1 },
    { -1 ,  1 },
    { -1 , -1 },
    { 1  ,  1 },
  };

static int              *g_i      = NULL;
static char             *g_buffer = NULL;

static bool
print_str_to_buffer(char const *str)
{
  int           printf_ret;

  if ((printf_ret = snprintf(g_buffer + (*g_i), VOIR_BUFFER_SIZE - (*g_i),
                             "%s", str)) < 0)
    {
      TRACE(RED"snprintf failed\n"WHITE);
      return (false);
    }
  *g_i += printf_ret;
  return (true);
}

static void
ht_callback_print_rsrc(void *data)
{
  t_item        *itemstack;
  size_t        i;
  char const    *rsrc_str;

  if (!(itemstack = data) || !g_buffer || !g_i)
    return ;
  if (!(rsrc_str = get_rsrc_string_from_enum(itemstack->type)))
    {
      TRACE(RED"invalid ressource type !"WHITE);
      return ;
    }
  i = 0;
  while (i < itemstack->amount)
    {
      print_str_to_buffer(" ");
      print_str_to_buffer(rsrc_str);
      ++i;
    }
}

static bool
up_down(t_cli *c)
{
  t_hash        *tile;
  int64_t       x;
  int64_t       y;
  int64_t       real_x;
  int64_t       real_y;
  int           nb_players;
  int           i;

  for (y = 0; y <= c->level; ++y)
    {
      for (x = -y; x <= y; ++x)
        {
          real_x = ((c->x_pos + (x * g_coef[c->direction].x)));
          real_y = ((c->y_pos + (y * g_coef[c->direction].y)));
          tile = t_map_at(&c->servptr->map, (t_coord){real_x, real_y});
          ERR("x:%ld ; y:%ld\n", real_x, real_y);
          nb_players = count_players_on_tile(c, (t_coord){real_x, real_y});
          for (i = 0; i < nb_players; ++i)
            print_str_to_buffer(&" joueur"[0/* (i > 0) ? 0 : 1 */]);
          ht_foreach(tile, &ht_callback_print_rsrc);
          print_str_to_buffer(((y == c->level && x == y)) ? "" : ",");
        }
    }
  return (true);
}

static bool
left_right(t_cli *c)
{
  t_hash        *tile;
  int64_t       x;
  int64_t       y;
  int64_t       real_x;
  int64_t       real_y;
  int           nb_players;
  int           i;

  for (x = 0; x <= c->level; ++x)
    {
      for (y = -x; y <= x; ++y)
        {
          real_x = ((c->x_pos + (x * g_coef[c->direction].x)));
          real_y = ((c->y_pos + (y * g_coef[c->direction].y)));
          tile = t_map_at(&c->servptr->map, (t_coord){real_x, real_y});
          ERR("x:%ld ; y:%ld\n", real_x, real_y);
          nb_players = count_players_on_tile(c, (t_coord){real_x, real_y});
          for (i = 0; i < nb_players; ++i)
            print_str_to_buffer(&" joueur"[0/* (i > 0) ? 0 : 1 */]);
          ht_foreach(tile, &ht_callback_print_rsrc);
          print_str_to_buffer(((y == c->level && x == y)) ? "" : ",");
        }
    }
  return (true);
}

bool
voir(t_cli *c, t_msg UNUSED(*msg))
{
  int           i;
  char          *buffer;

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);

  i = 0;
  if (!(buffer = malloc(VOIR_BUFFER_SIZE)))
    return (perror("malloc()"), false);
  *buffer = '\0';
  g_i = &i;
  g_buffer = buffer;
  print_str_to_buffer("{");
  if (c->direction == UP || c->direction == DOWN)
    up_down(c);
  else
    left_right(c);
  print_str_to_buffer("}\n");
  enqueue_msg(c, buffer);
  free(buffer);

  return (true);
}
