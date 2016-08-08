/*
** map.h for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/t_opt
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Jun 11 09:33:07 2016 querat_g
** Last update Sun Jun 12 16:22:52 2016 querat_g
*/

#ifndef MAP_H_
# define MAP_H_

#include <stdbool.h>
#include <stdint.h>
#include "zappy.h"
#include "hash.h"

typedef struct          s_map
{
  int64_t               width;
  int64_t               height;
  t_hash                ***map;
}                       t_map;

bool            t_map_dest(t_map *map);
bool            t_map_const(t_map *map, size_t width, size_t height);
bool            t_map_add_item(t_map *map, enum e_rsrc rsrc,
                               t_coord cd, size_t amount);
size_t          t_map_take_item(t_map *map, enum e_rsrc rsrc,
                               t_coord cd, size_t amount);
t_hash          *t_map_at(t_map *map, t_coord c);

bool            dump_map(t_map *map);
void            dump_tile(void *t);

#endif
