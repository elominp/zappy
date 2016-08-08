/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Mon Jun 20 17:50:40 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

//
// I capped the max speed at µms.
//
bool
sst(t_cli *c, t_msg *msg)
{
  char		buff[32];
  int		i;
  uint64_t	new_time;

  i = 0;
  memset(buff, 0, 32);
  if (msg == NULL || msg->params == NULL || msg->params->first == NULL ||
      msg->params->first->data == NULL ||
      (new_time = atol((char *)msg->params->first->data)) == 0)
    {
      ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
          __func__, c->sock.fd, c->team->name);
      ERR(RED"   invalid parameter\n"WHITE);
      return (false);
    }
  if (new_time <= 1000000)
    c->servptr->opt->time = new_time;
  else
    c->servptr->opt->time = 1000;
  i = snprintf(buff, 32, "sst ");
  i += snprintf(buff, 32 - i, "%lu\n", c->servptr->opt->time);
  enqueue_msg(c, buff);
  return (true);
}
