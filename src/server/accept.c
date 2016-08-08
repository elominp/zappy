/*
** accept.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 21 14:39:44 2016 querat_g
** Last update Mon Jun 13 11:35:27 2016 querat_g
*/

#include "server.h"

bool            try_accept(t_serv *s)
{
  t_cli         *newclient;

  if (FD_ISSET(s->connectsock.fd, &s->fdset_read))
    {
      ERR("Client waiting in connection socket !\n");
      newclient = new_t_cli(s);
      if (newclient)
        {
          if (!ht_add_entry(s->clients, newclient, &newclient->sock.fd,
                            sizeof(newclient->sock.fd)))
            ERR("ht_add_entry failed !\n");
        }
      else
        return (ERR("could not accept connection !\n"), false);
      ERR("client %d connected !\n", newclient->sock.fd);
    }

  return (true);
}
