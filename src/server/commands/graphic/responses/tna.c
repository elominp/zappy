/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Mon Jun 20 17:50:46 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static  char	buff[1024];

static t_node
*get_first_team(t_serv *s)
{
  if (s->teams == NULL || s->teams->first == NULL)
    return (NULL);
  return (s->teams->first);
}

static void
prepare_message(t_node *current)
{
  t_team *team;

  memset(buff, 0, 1024);
  if (current->next == NULL || (team = current->data) == NULL ||
      team->name == NULL)
    return ;
  snprintf(buff, 5, "tna ");
  snprintf(buff + 4, 1020, "%s\n", team->name);
}

bool
tna(t_cli *c, t_msg *msg)
{
  t_node *current;

  (void)msg;
  if ((current = get_first_team(c->servptr)) == NULL)
    {
      ERR(PINK"[%s], client %d from team '%s': Cannot get teams\n"WHITE,
	  __func__, c->sock.fd, c->team->name);
    }
  while (current != NULL)
    {
      prepare_message(current);
      enqueue_msg(c, buff);
      current = current->next;
    }
  return (true);
}
