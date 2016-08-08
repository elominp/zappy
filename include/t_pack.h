/*
** t_pack.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon Jun 13 18:18:49 2016 querat_g
// Last update Thu Jun 23 12:29:18 2016 querat_g
*/

#ifndef T_PACK_H_
# define T_PACK_H_

# include <stdlib.h>
# include <stdbool.h>

typedef struct          s_packet
{
  size_t                size;
  size_t                offset;
  void                  *string;
}                       t_pack;

bool            t_pack_dest(t_pack *pack);
bool            t_pack_const(t_pack *pack, char *msg);
t_pack          *new_t_pack(char *msg);
void            *delete_t_pack(t_pack *pack);
void            delete_t_pack_hook(void *pack);

#endif
