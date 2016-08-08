/*
** process_output.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Jun 10 09:43:42 2016 querat_g
** Last update Thu Jun 23 16:01:42 2016 querat_g
*/

#include <sys/poll.h>
#include "server.h"

static bool
fd_is_ready_to_write(int fd)
{
  int           ret;
  struct pollfd poll_;

  poll_.fd      = fd;
  poll_.events  = POLLOUT;
  poll_.revents = 0;

  if ((ret = poll(&poll_, 1, 0)) < 0)
    {
      TRACE(RED" could not poll(fd %d) !"WHITE, fd);
      return (false);
    }

  return ((poll_.revents & POLLOUT) ? true : false);
}

static bool
write_while_you_still_can(t_cli *c)
{
  t_pack        *pack;
  int           ret;

  if (!c || !c->outqueue ||
      !fd_is_ready_to_write(c->sock.fd) ||
      !(pack = LIST_FIRST_DATA(c->outqueue)))
    return (false);

  if (FAILS(ret = write((c->sock.fd),
                        (pack->string + (uintptr_t)pack->offset),
                        (pack->size - pack->offset))))
    {
      TRACE(RED"write failed for client %d !"WHITE, c->sock.fd);
      return (false);
    }

  pack->offset += ret;
  if (pack->offset >= pack->size)
    c->outqueue->rm_first_node(c->outqueue, &delete_t_pack_hook);

  return (true);
}

void
process_output_queue(void *data)
{
  t_cli                 *cli;
  t_pack                *pack;

  if (!(cli = data) || !cli->outqueue ||
      !(pack = LIST_FIRST_DATA(cli->outqueue)))
    return ;

  if (!FD_ISSET(cli->sock.fd, &cli->servptr->fdset_write))
    return ;

  while (write_while_you_still_can(cli))
    {}

  return ;
}

void
process_clients_output(t_serv *s)
{
  if (!s || !s->clients)
    return ;
  ht_foreach(s->clients, &process_output_queue);
}
