/*
** broadcast.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 11:20:09 2016 querat_g
** Last update Sat Jun 25 10:27:39 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "server.h"
#include "macros.h"

static t_coord          g_origin = {0, 0};
static t_map            *g_map;

static int64_t
circ_x(int64_t x)
{
  return ((x < 0)
          ? ((g_map->width) + (x % g_map->width))
          : (x % g_map->width));
}

static int64_t
circ_y(int64_t y)
{
  return (y = (y < 0)
          ? ((g_map->height) + (y % g_map->height))
          : (y % g_map->height));
}

static void
build_coordinates_diff(t_coord *c, t_coord diff[9])
{
  diff[M_SAME_TILE ].x = (c->x             - g_origin.x);
  diff[M_SAME_TILE ].y = (c->y             - g_origin.y);
  diff[M_UP        ].x = (c->x             - g_origin.x);
  diff[M_UP        ].y = (circ_y(c->y - 1) - g_origin.y);
  diff[M_DOWN      ].x = (c->x             - g_origin.x);
  diff[M_DOWN      ].y = (circ_y(c->y + 1) - g_origin.y);
  diff[M_RIGHT     ].x = (circ_x(c->x + 1) - g_origin.x);
  diff[M_RIGHT     ].y = (circ_y(c->y)     - g_origin.y);
  diff[M_LEFT      ].x = (circ_x(c->x - 1) - g_origin.x);
  diff[M_LEFT      ].y = (circ_y(c->y)     - g_origin.y);
  diff[M_UP_LEFT   ].x = (circ_x(c->x - 1) - g_origin.x);
  diff[M_UP_LEFT   ].y = (circ_y(c->y - 1) - g_origin.y);
  diff[M_UP_RIGHT  ].x = (circ_x(c->x + 1) - g_origin.x);
  diff[M_UP_RIGHT  ].y = (circ_y(c->y - 1) - g_origin.y);
  diff[M_DOWN_RIGHT].x = (circ_x(c->x + 1) - g_origin.x);
  diff[M_DOWN_RIGHT].y = (circ_y(c->y + 1) - g_origin.y);
  diff[M_DOWN_LEFT ].x = (circ_x(c->x - 1) - g_origin.x);
  diff[M_DOWN_LEFT ].y = (circ_y(c->y + 1) - g_origin.y);
}

static char const       *g_msg = "";
static int              g_calling_client_id = 0;

static void
for_serv_clients_as_client(void *voidclient)
{
  t_cli         *c;
  double        distances[9];
  t_coord       diff[9];
  int           min_index;

  if (!(c = voidclient) || c->is_graphic)
    return ;
  ERR(WWHITE"CLIENT %d\n"WHITE, c->sock.fd);
  memset(distances, 0, sizeof(distances));
  build_coordinates_diff(&(t_coord){c->x_pos, c->y_pos}, diff);
  build_distances(diff, distances);
  min_index = get_min_distance_index(distances);
  min_index = convert_index_according_to_direction(c, c->direction, min_index);

  if (c->sock.fd != g_calling_client_id)
    send_broadcast(c, g_msg, min_index);

  #ifdef __DEBUG__
  print_matrix(diff);
  print_distances(distances);
  ERR(PINK"final: %d\n"WHITE, min_index);
  #endif
}

bool
broadcast(t_cli *c, t_msg *msg)
{
  char const    *str;

  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
      __func__, c->sock.fd, c->team->name);
  str = msg->raw + sizeof("broadcast") - 1;
  if (!(*str) || !(*(str + 1)))
    return (ERR(PINK"NULL"RED" broadcast\n"WHITE), false);
  ++str;
  ERR(YELLOW"broadcasting: \"%s\"\n", str);

  g_msg = str;
  g_map = &c->servptr->map;
  g_origin.x = c->x_pos;
  g_origin.y = c->y_pos;
  g_calling_client_id = c->sock.fd;

  ht_foreach(c->servptr->clients, &for_serv_clients_as_client);
  enqueue_msg(c, "ok\n");
  pbc(c, str);
  return (true);
}
