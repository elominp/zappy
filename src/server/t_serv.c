/*
** t_serv.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed May 18 11:23:31 2016 querat_g
** Last update Sat Jun 25 15:24:04 2016 querat_g
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include "server.h"

static bool             t_sock_dest(t_sock *s)
{
  if (!s)
    return (false);
  if (ISVALIDFD(s->fd))
    {
      shutdown(s->fd, SHUT_RDWR);
      close(s->fd);
    }
  ZERO_MEM(s);
  return (false);
}

static bool             t_sock_const(t_sock *s, uint16_t port)
{
  struct protoent       *ent;
  int   yeah;

  if (!s)
    return (false);
  ZERO_MEM(s);
  if ((ent = getprotobyname("tcp")) == NULL)
    return (perror("getprotobyname()"), false);
  if (FAILS(s->fd = socket(AF_INET, SOCK_STREAM, ent->p_proto)))
    return (perror("socket()"), false);
  s->sin.sin_family = AF_INET;
  s->sin.sin_port = htons(port);
  s->sin.sin_addr.s_addr = htonl(INADDR_ANY);
  yeah = 1;
  if (setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, &yeah, sizeof(int)) == -1)
    return (perror("setsockopt() failed: "), false);
  if (FAILS(bind(s->fd, (struct sockaddr*)&s->sin, sizeof(s->sin))))
    return (perror("bind()"), false);
  if (FAILS(listen(s->fd, MAX_CLIENTS)))
    return (perror("listen"), false);
  return (true);
}

bool            t_serv_dest(t_serv *s)
{
  ASSERT(s != NULL);
  if (!s)
    return (false);
  t_sock_dest(&s->connectsock);
  if (s->clients)
    ht_free(s->clients, &delete_t_cli_hook);
  t_map_dest(&s->map);
  t_opt_dest(s->opt);
  if (s->teams)
    list_destruct(&s->teams, &delete_t_team);
  ZERO_MEM(s);
  return (false);
}

bool            t_serv_const(t_serv *s, t_opt *opt)
{
  int32_t       port;

  ASSERT(s != NULL && str != NULL);
  if (!s)
    return (false);
  ZERO_MEM(s);
  s->opt = opt;
  port = opt->port;
  if (port <= 0 || port > 0xFFFF)
    return (TRACE("Invalid port argument (<= 0 || > 65535)\n"), false);
  if (!(s->clients = ht_init(10)))
    return (TRACE("ht_init failed !\n"), t_serv_dest(s), false);
  if (!t_map_const(&s->map, opt->x_size, opt->y_size))
    return (ERR("t_map_const() failed\n"), t_serv_dest(s), false);
  FD_ZERO(&s->fdset_read);
  FD_ZERO(&s->fdset_write);
  s->teams = opt->teams;
  opt->teams = NULL;
  s->prev_egg_id = 0;
  if (!t_sock_const(&s->connectsock, (uint16_t)port))
    return (t_serv_dest(s), false);
  return (true);
}
