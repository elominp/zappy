/*
** t_opt_dump.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Jun 10 11:26:57 2016 querat_g
** Last update Thu Jun 23 16:04:53 2016 querat_g
*/

#include "server.h"

void
err_hook(void *data)
{
  if (!data)
    return ;
  ERR(GREEN"    ->%s\n"WHITE, data ? ((t_team*)data)->name : "NULL");
}

void
debug_dump_opts(t_opt *opt)
{
#ifdef __DEBUG__
  ERR(BLUE
      "Dumping t_opt:\n"
      "uint64_t              x_size      = %lu\n"
      "uint64_t              y_size      = %lu\n"
      "uint64_t              port        = %lu\n"
      "uint64_t              max_clients = %lu\n"
      "uint64_t              time        = %lu\n"
      "t_list                *teams:\n"
      WHITE,
      opt->x_size,
      opt->y_size,
      opt->port,
      opt->max_clients,
      opt->time);
  list_print(opt->teams, &err_hook);
  ERR(BLUE"-----------------------------------------\n"WHITE);
#else
  (void)opt;
#endif
}
