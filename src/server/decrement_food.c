/*
** decrement_food.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 21 15:11:10 2016 querat_g
** Last update Fri Jun 24 16:32:20 2016 querat_g
*/

#include "server.h"

static float    g_time;
static t_list   *eggs_to_remove;
static t_team   *actual_team;

static int  get_egg_offset(t_team *team, int64_t id)
{
  t_list    *eggs;
  t_node    *node;
  t_egg     *egg;
  int       offset;

  if (team == NULL || (eggs = team->eggs_sorted) == NULL ||
      (node = eggs->first) == NULL)
    return (-1);
  offset = 0;
  while (node != NULL)
  {
    if ((egg = node->data) != NULL && egg->id == id)
      return (offset);
    offset++;
    node = node->next;
  }
  return (-1);
}

int     remove_egg(void *ded, void *useless)
{
  t_ded *ded_egg;
  int   offset;

  if ((ded_egg = ded) == NULL ||
      ded_egg->team == NULL || ded_egg->egg == NULL ||
      (offset = get_egg_offset(ded_egg->team, ded_egg->egg->id)) < 0)
    return (false);
  (void)useless;
  ht_rm_entry(ded_egg->team->eggs, &(ded_egg->egg->id),
              sizeof(ded_egg->egg->id), free);
  list_rm_node(ded_egg->team->eggs_sorted, offset, NULL);
  return (true);
}

static void
client_as_servclient(void *voidclient)
{
  t_cli         *cli;

  if (!(cli = voidclient) || !(cli->team) || cli->is_graphic)
    return ;

  cli->food -= (g_time);
  if (cli->food <= 0.f)
    {
      if (take_from_client(cli, NOURRITURE, 1) <= 0)
        {
          ERR(RED"%d DED of hunger\n"WHITE, cli->sock.fd);
          pdi(cli);
          kick_client(cli->servptr, cli->sock.fd);
          return ;
        }
      cli->food = 126.f;
    }
}

static int
decrement_food_eggs(void *ptr_egg, void *ptr_serv){
  t_egg     *egg;
  t_ded     *ded;
  t_serv    *serv;

  if ((egg = ptr_egg) == NULL || (serv = ptr_serv) == NULL)
    return (0);
  egg->life_time -= g_time;
  if (egg->life_time <= 0.)
  {
    ERR(RED"%ld egg DED of hunger\n"WHITE, egg->id);
    ded = calloc(1, sizeof(t_ded));
    ded->team = actual_team;
    ded->egg = egg;
    list_append(&eggs_to_remove, ded);
    edi(serv->clients, egg);
  }
  return (0);
}

static int  decrement_food_eggs_teams(void *ptr_team, void *serv)
{
  t_team    *team;

  if ((team = ptr_team) == NULL)
    return (false);
  actual_team = team;
  list_for_each(team->eggs_sorted, decrement_food_eggs, serv);
  return (true);
}

int
decrement_food(t_serv *serv)
{
  g_time = my_clock();
  g_time /= (1000.f / serv->opt->time);

  ht_foreach(serv->clients, &client_as_servclient);
  eggs_to_remove = new_list();
  list_for_each(serv->teams, decrement_food_eggs_teams, serv);
  list_for_each(eggs_to_remove, remove_egg, NULL);
  list_destruct(&eggs_to_remove, NULL);
  return (0);
}
