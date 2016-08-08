/*
** build_distances.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Jun 16 18:20:49 2016 querat_g
** Last update Thu Jun 16 18:21:08 2016 querat_g
*/

#include <math.h>
#include "server.h"

void
build_distances(t_coord diff[9], double *dist)
{
  int           i;

  for (i = 0; i < 9; ++i)
    dist[i] = (sqrt(pow(diff[i].x, 2) + pow(diff[i].y, 2)));
}
