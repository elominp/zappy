/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 23 16:10:52 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

bool
msz(t_cli *c, t_msg UNUSED(*msg))
{
  char	buff[256];

  snprintf(buff, 64, "msz %ld %ld\n",
           c->servptr->map.width,
           c->servptr->map.height);
  enqueue_msg(c, buff);
  return (true);
}
