/*
** select.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 21 14:36:43 2016 querat_g
** Last update Sat May 21 14:39:09 2016 querat_g
*/

#include <stdlib.h>
#include <sys/select.h>
#include "server.h"
#include "hash.h"

static void     for_each_client_fd_set(void *client)
{
  t_cli                         *c;

  if (!(c = client))
    {
      DEBUG("NULL client, shouldn't happen !\n");
      return ;
    }

  FD_SET(c->sock.fd, &c->servptr->fdset_read);
  FD_SET(c->sock.fd, &c->servptr->fdset_write);

  if (c->sock.fd > c->servptr->maxfd)
    c->servptr->maxfd = c->sock.fd;
}

int             my_select(t_serv *s)
{
  FD_ZERO(&s->fdset_read);
  FD_ZERO(&s->fdset_write);
  FD_SET(STDIN_FILENO, &s->fdset_read);
  FD_SET(s->connectsock.fd, &s->fdset_read);

  s->maxfd = s->connectsock.fd;
  ht_foreach(s->clients, &for_each_client_fd_set);

  return (select(s->maxfd + 1, &s->fdset_read, &s->fdset_write, NULL, NULL));
}
