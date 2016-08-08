/*
** t_chan.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Jun  2 10:37:33 2016 querat_g
** Last update Sun Jun  5 20:04:20 2016 querat_g
*/

#include "server.h"
#include "list.h"

void
t_chan_print(void *d)
{
  t_chan        *c;

  if (!(c = d))
    return ;
  ERR("CHANNEL %s -------------------------\n", c->name ? c->name : "NULL)");
  c->clients->print(c->clients, NULL);
  ERR("------------------------------------\n");
}

bool
t_chan_dest(t_chan *c)
{
  if (!c)
    return (false);
  if (c->name)
    free(c->name);
  if (c->clients)
    c->clients->destruct(&c->clients, free);
  ZERO_MEM(c);
  return (false);
}

void
delete_t_chan(void *data)
{
  t_chan        *c;

  if (!(c = data))
    return ;
  t_chan_dest(c);
  free(c);
}

bool
t_chan_const(t_chan *c, char *name)
{
  if (!c || !name)
    {
      TRACE("NULL %s", c ? "name" : "client");
      return (false);
    }
  c->name = strdup(name);
  if (!c->name)
    return (perror("strdup()"), false);
  if (!(c->clients = new_list()))
    return (TRACE("new_list() failed"), t_chan_dest(c));
  return (true);
}

t_chan
*new_t_chan(char *name)
{
  t_chan *c;

  c = malloc(sizeof(*c));
  if (!c)
    return (perror("malloc()"), NULL);
  if (!t_chan_const(c, name))
    return (free(c), NULL);
  return (c);
}
