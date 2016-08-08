/*
** client_input.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 21 16:49:03 2016 querat_g
** Last update Fri Jun 17 15:02:47 2016 querat_g
*/

#include <sys/select.h>
#include "server.h"
#include "hash.h"
#include "circularbuffer.h"

static void
process_client_input(void *data)
{
  t_cli         *c;
  int           rd;
  char          buf[CIRCULAR_BUF_SIZE];

  if (!(c = data))
    return ;

  if (FD_ISSET(c->sock.fd, &c->servptr->fdset_read))
    {
      DEBUG("Processing client %d\n", c->sock.fd);
      if ((rd = read(c->sock.fd, buf, sizeof(buf) - 1)) <= 0)
        {
          ERR(YELLOW"Client %d disconnected\n"WHITE, c->sock.fd);
          kick_client(c->servptr, c->sock.fd);
          return ;
        }
      c->buffer.overwrite(&c->buffer, buf, rd);
    }
}

void
process_clients_input(t_serv *s)
{
  ht_foreach(s->clients, &process_client_input);
}
