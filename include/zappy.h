/*
** zappy.h for  in /home/querat_g/tmp/PSU_2015_zappy/inc
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun  7 12:27:15 2016 querat_g
// Last update Wed Jun 22 17:54:13 2016 querat_g
*/

#ifndef ZAPPY_H_
# define ZAPPY_H_

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

# define JOUEUR         0

typedef enum            e_rsrc
  {
    NOURRITURE,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    INVALID
  }                     t_rsrc;

typedef enum            e_orient
  {
    M_SAME_TILE = 0,
    M_UP = 1,
    M_UP_LEFT = 2,
    M_LEFT = 3,
    M_DOWN_LEFT = 4,
    M_DOWN = 5,
    M_DOWN_RIGHT = 6,
    M_RIGHT = 7,
    M_UP_RIGHT = 8,
  }                     t_or;

typedef struct          s_coord
{
  int64_t               x;
  int64_t               y;
}                       t_coord;

typedef struct          s_rsrc_to_string
{
  enum e_rsrc          enumeration;
  char const            *string;
}                       t_rsrc_to_string;

typedef struct          s_item
{
  enum e_rsrc          type;
  size_t               amount;
}                       t_item;

extern const struct s_rsrc_to_string   g_rsrc_to_string[];

enum e_rsrc     get_rsrc_enum_from_string(char const *str);
char const      *get_rsrc_string_from_enum(enum e_rsrc res);

t_coord         make_t_coord(size_t x, size_t y);

#endif
