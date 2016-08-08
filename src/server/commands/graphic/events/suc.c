/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
** 
** Made by schmou_a
** Login   <schmou@epitech.net>
** 
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 16 16:55:57 2016 schmou_a
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

bool
suc(t_cli *c)
{
  char	buff[8];

  snprintf(buff, 5, "suc\n");
  enqueue_msg(c, buff);
  return (true);
}
