/*
** send.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai/broadcast
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Jun 17 10:26:49 2016 querat_g
** Last update Sat Jun 25 11:15:20 2016 querat_g
*/

#include <stdio.h>
#include "server.h"

bool
send_broadcast(t_cli *c, char const *msg, int min_index)
{
  char  buffer[2048];

  *buffer = '\0';
  snprintf(buffer, sizeof(buffer),
           "message %d,%s\n",
           min_index, msg);
  enqueue_msg(c, buffer);
  return (true);
}
