/*
** init_vars.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Jun 26 14:39:54 2016 querat_g
** Last update Sun Jun 26 14:40:07 2016 querat_g
*/

#include "server.h"

void
init_cli_vars(t_cli *c, t_serv *s)
{
  c->servptr = s;
  c->level = 1;
  c->direction = rand() % 4;
  c->x_pos = rand() % c->servptr->map.width;
  c->y_pos = rand() % c->servptr->map.height;
}
