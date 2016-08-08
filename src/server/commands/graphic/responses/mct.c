/*
** broadcast.c for  in /home/schmou/SysUnix/PSU_2015_zappy/src/server/commands/graphic
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:54:39 2016 schmou_a
** Last update Thu Jun 23 12:31:54 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static void
prepare_message(t_list *p, int x, int y)
{
  memset(p->first->data, 0, 10);
  snprintf(p->first->data, 10, "%d", x);
  memset(p->first->next->data, 0, 10);
  snprintf(p->first->next->data, 10, "%d", y);
}

/*
** I know it seems strange to have a shitload of spaces as data,
** but I need room for a potential high number of characters
*/
static bool
init_list(t_list *p)
{
  char	*space;

  if ((space = strdup("          ")) == NULL)
    return (ERR(RED"Omg malloc failed, BAIL OUT BAIL OUT\n"WHITE), false);
  list_append(&p, space);
  if ((space = strdup("          ")) == NULL)
    return (ERR(RED"Omg malloc failed, BAIL OUT BAIL OUT\n"WHITE), false);
  list_append(&p, space);
  return (true);
}

bool
mct(t_cli *c, t_msg *msg)
{
  int64_t	x;
  int64_t	y;
  int64_t	xmax;
  int64_t	ymax;
  t_list	*params;

  (void)msg;
  x = 0;
  y = 0;
  xmax = c->servptr->map.width;
  ymax = c->servptr->map.height;
  if ((params = new_list()) == NULL || init_list(params) == false)
    return (ERR(RED"Omg malloc failed, BAIL OUT BAIL OUT\n"WHITE), false);
  while (y <= xmax)
    {
      while (x <= ymax)
	{
	  prepare_message(params, x, y);
	  bct(c, &(t_msg){NULL, "bct", params, 0});
	  x++;
	}
      x = 0;
      y++;
    }
  return (list_destruct(&params, &free), true);
}
