/*
** direction.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Jun 24 16:59:08 2016 querat_g
** Last update Sat Jun 25 16:48:21 2016 querat_g
*/

#include "server.h"

int
to_graphical_dir(enum e_dir dir)
{
  static int const g_to_graphical_protocol[] = { 1, 3, 4, 2 };

  return (g_to_graphical_protocol[dir]);
}
