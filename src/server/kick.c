/*
** kick.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 21 18:17:06 2016 querat_g
** Last update Sat Jun 25 10:10:32 2016 querat_g
*/

#include "server.h"

static int
decrement(void *data, void *team)
{
  if (!data || !((t_team*)data)->name || !team)
    return (-1);

  if (!strcmp(((t_team*)data)->name, team))
    --((t_team*)data)->nb_members;
  return (0);
}

/*
** removes the kebab
*/
bool
kick_client(t_serv *s, int id)
{
  t_cli *cli;

  cli = ht_get_entry(s->clients, &id, sizeof(id));
  if (!cli)
    return (false);

  ERR(RED"Ded-ing client %d \n"WHITE, cli->sock.fd);
  list_for_each(s->teams, &decrement, cli->team);

  if (is_ready_to_write(cli->sock.fd, 0))
    write(cli->sock.fd, SAFE_STR("mort\n"));
  pdi(cli);
  ht_rm_entry(s->clients, &id, sizeof(id),
              &delete_t_cli_hook);
  return (true);
}
