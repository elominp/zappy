/*
** t_cli.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed May 18 11:36:07 2016 querat_g
** Last update Sun Jun 26 15:04:51 2016 schmou_a
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include "server.h"

bool            t_cli_dest(t_cli *c)
{
  if (!c)
    return (TRACE("NULL t_cli !\n"), false);
  t_circ_dest(&c->buffer);
  if (ISVALIDFD(c->sock.fd))
    {
      shutdown(c->sock.fd, SHUT_RDWR);
      close(c->sock.fd);
    }
  if (c->ip)
    free(c->ip);
  if (c->outqueue)
    c->outqueue->destruct(&c->outqueue, &delete_t_pack_hook);
  if (c->inventory)
    ht_free(c->inventory, &free);
  if (c->commands)
    list_destruct(&c->commands, &delete_t_msg);
  ZERO_MEM(c);
  return (false);
}

bool            t_cli_const(t_cli *c, t_serv *s)
{
  unsigned int  sz;

  ASSERT(c != NULL && s != NULL);
  if (!c || !s)
    return (TRACE(RED"invalid parameter\n"WHITE), false);
  ZERO_MEM(c);
  if (!ISVALIDFD(s->connectsock.fd))
    return (TRACE(RED"invalid server socket !\n"WHITE), false);
  if (!(c->inventory = ht_init(2)))
    return (TRACE(RED"ht_init() failed"), t_cli_dest(c), false);
  if ((!(c->outqueue = new_list()))
      || (!(t_circ_const(&c->buffer, CIRCULAR_BUF_SIZE)))
      || (!(c->commands = new_list())))
    return (TRACE(RED"t_const_*() failed\n"WHITE), t_cli_dest(c), false);
  init_cli_vars(c, s);
  sz = sizeof(c->sock.sin);
  c->sock.fd = accept(s->connectsock.fd, (struct sockaddr*)&c->sock.sin, &sz);
  if (c->sock.fd == -1)
    return (perror("accept()"), t_cli_dest(c), false);
  c->ip = strdup(inet_ntoa(c->sock.sin.sin_addr));
  if (!c->ip)
    return (perror("strdup"), t_cli_dest(c));
  enqueue_msg(c, WELCOME);
  s->connected_clients++;
  return (give_to_client(c, NOURRITURE, 10), true);
}

t_cli           *new_t_cli(t_serv *s)
{
  t_cli         *c;

  if (s->connected_clients == 100)
    return (TRACE(RED"max number of clients reached !\n"WHITE), NULL);
  c = calloc(sizeof(t_cli), 1);
  if (!c)
    return (perror("calloc()"), NULL);
  if (!t_cli_const(c, s))
    return (free(c), NULL);
  return (c);
}

t_cli           *delete_t_cli(t_cli *cli)
{
  if (!cli)
    return (NULL);
  cli->servptr->connected_clients -= 1;
  t_cli_dest(cli);
  free(cli);
  return (NULL);
}

void            delete_t_cli_hook(void *c)
{
  delete_t_cli(c);
}
