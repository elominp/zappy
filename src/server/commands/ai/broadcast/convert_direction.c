/*
** convert_direction.c for  in /src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Jun 16 18:36:16 2016 querat_g
** Last update Thu Jun 23 16:06:21 2016 querat_g
*/

#include "server.h"

/*
** ^   ->   ^
** pretty straightforward ...
*/
static int const        g_up_to_up[9]    = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

/*
**   ^       \/
** 2 1 8    6 5 4
** 3 0 7 -> 7 0 3
** 4 5 6    8 1 2
*/
static int const        g_up_to_down[9]  = { 0, 5, 6, 7, 8, 1, 2, 3, 4 };

/*
**   ^        <-
** 2 1 8    8 7 6
** 3 0 7 -> 1 0 5
** 4 5 6    2 3 4
*/
static int const        g_up_to_left[9]  = { 0, 7, 8, 1, 2, 3, 4, 5, 6 };

/*
**   ^        ->
** 2 1 8    4 3 2
** 3 0 7 -> 5 0 1
** 4 5 6    6 7 8
*/
static int const        g_up_to_right[9] = { 0, 3, 4, 5, 6, 7, 8, 1, 2 };

/*
** Selects the converting array according to client's direction
** UP
** DOWN
** LEFT
** RIGHT
*/
static int const        *g_corresp[] =
  {
    g_up_to_up,
    g_up_to_down,
    g_up_to_left,
    g_up_to_right
  };

int
convert_index_according_to_direction(t_cli *c, t_dir UNUSED(dir),
                                     int min_index)
{
  if (c->direction > 3 || min_index > 8)
    return (0);
  return (g_corresp[c->direction][min_index]);
}
