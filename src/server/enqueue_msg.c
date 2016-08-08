/*
** send_code.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 18:08:53 2016 querat_g
** Last update Wed Jun  8 17:30:29 2016 querat_g
*/

#include "server.h"

bool
enqueue_msg(t_cli *c, char *msg)
{
  t_pack        *pack;

  if (!c || !msg || !c->outqueue)
    return (TRACE("NULL msg ...\n"), false);

  if (!(pack = new_t_pack(msg)))
    return (TRACE("new_t_pack() failed !\n"), false);

  if (!(c->outqueue->append(&c->outqueue, pack)))
    {
      TRACE("list_append() failed !n");
      delete_t_pack(pack);
      return (false);
    }
  return (true);
}
