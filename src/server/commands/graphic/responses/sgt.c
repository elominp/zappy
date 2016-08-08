/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
** 
** Made by schmou_a
** Login   <schmou@epitech.net>
** 
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Wed Jun 15 16:01:46 2016 schmou_a
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

bool
sgt(t_cli *c, t_msg *msg)
{
  char	buff[32];

  (void)msg;
  snprintf(buff, 32, "sgt %lu\n", c->servptr->opt->time);
  enqueue_msg(c, buff);
  return (true);
}
