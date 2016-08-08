/*
** t_opt.h for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon Jun 13 18:16:33 2016 querat_g
// Last update Thu Jun 23 11:32:08 2016 querat_g
*/

#ifndef T_OPT_H_
# define T_OPT_H_

# define COMMAND_LINE_OPTS      "p:x:y:n:c:t:"

# define MAX_TILE_NUMBER        40000

typedef struct          s_opt
{
  uint64_t              x_size;
  uint64_t              y_size;
  uint64_t              port;
  uint64_t              max_clients;
  uint64_t              time;
  t_list                *teams;
}                       t_opt;

typedef struct          s_optcor
{
  int                   character;
  uint64_t              *opttoaffect;
}                       t_optcor;

bool            t_opt_dest(t_opt *o);
bool            t_opt_const(t_opt *o, int ac, char **av);
bool            parse_av(t_opt *o, int ac, char **av);
void            usage(char **av);
void            debug_dump_opts(t_opt *opt);

#endif
