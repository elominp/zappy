/*
** min.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Jun 16 18:26:24 2016 querat_g
** Last update Fri Jun 17 10:03:35 2016 querat_g
*/

#include "server.h"
#include "macros.h"

int
get_min_distance_index(double *distances)
{
  int           i;
  double        min;
  int           minoffset;

  min = 10000000;
  minoffset = 0;

  for (i = 0; i < 9; ++i)
    {
      if (distances[i] < min)
        {
          min = distances[i];
          minoffset = i;
        }
    }

  return (minoffset);
}
