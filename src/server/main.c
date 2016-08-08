/*
** main.c for  in /home/querat_g/tmp/PSU_2015_myirc/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon May 16 11:02:34 2016 querat_g
** Last update Sat Jun 25 16:48:31 2016 querat_g
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myirc.h"
#include "server.h"

void
delete_t_msg(void *voidmsg)
{
  t_msg         *msg;

  if (!(msg = voidmsg))
    return ;
  if (msg->params)
    list_destruct(&msg->params, &free);
  if (msg->command)
    free(msg->command);
  free(msg);
}

void
client_as_servclient_exec_delayed(void *voidclient)
{
  t_cli         *c;
  t_msg         *msg;

  if (!(c = voidclient))
    return ;
  if (!(msg = LIST_FIRST_DATA(c->commands)))
    return ;
  if (c->servptr->current_time > msg->exec_after)
    {
      exec_ai_command(c, msg);
      list_rm_first_node(c->commands, &delete_t_msg);
      if ((msg = LIST_FIRST_DATA(c->commands)) &&
          !strcmp(msg->command, "incantation"))
        pic(c);
      return ;
    }
}

int
exec_delayed_ai_commands(t_serv *s)
{
  ht_foreach(s->clients, &client_as_servclient_exec_delayed);
  return (0);
}

int
server_loop(t_serv *s)
{
  while (!s->exit)
    {
      if (FAILS(my_select(s)))
        return (perror("select()"), EXIT_FAILURE);

      s->current_time = gettimeofday_ms();

      process_serverside_actions(s);

      try_accept(s);

      process_clients_input(s);
      process_clients_output(s);

      parse_and_exec_clients_commands(s);
      exec_delayed_ai_commands(s);

      decrement_food(s);

      usleep(0);
    }
  return (EXIT_SUCCESS);
}

int
main(int ac, char **av)
{
  t_serv                serv;
  int                   ret;
  t_opt                 opt;

  if (!t_opt_const(&opt, ac, av))
    return (EXIT_FAILURE);
  debug_dump_opts(&opt);
  if (!t_serv_const(&serv, &opt))
    return (EXIT_FAILURE);
  signals(&serv);
#ifdef __DEBUG__
  t_map_add_item(&serv.map, LINEMATE  , (t_coord){ 0, 0 }, 3);
  t_map_add_item(&serv.map, NOURRITURE, (t_coord){ 0, 0 }, 1);
  t_map_add_item(&serv.map, SIBUR     , (t_coord){ 0, 0 }, 2);
  t_map_add_item(&serv.map, THYSTAME  , (t_coord){ 0, 0 }, 2);
  t_map_add_item(&serv.map, DERAUMERE , (t_coord){ 0, 1 }, 1);
#endif
  if (populate_map(&serv.map) < 0)
    return (t_serv_dest(&serv), EXIT_FAILURE);
  ret = server_loop(&serv);
  t_serv_dest(&serv);
  return (ret);
}
