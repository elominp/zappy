/*
** t_pack.c for  in /home/querat_g/tmp/PSU_2015_myirc/inc
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Jun  1 10:33:32 2016 querat_g
** Last update Wed Jun  1 11:39:48 2016 querat_g
*/

#include "server.h"

bool
t_pack_dest(t_pack *pack)
{
  if (!pack)
    return (false);

  if (pack->string)
    free(pack->string);

  return (false);
}

void
*delete_t_pack(t_pack *pack)
{
  if (!pack)
    return (NULL);

  t_pack_dest(pack);
  free(pack);
  return (NULL);
}

void
delete_t_pack_hook(void *pack)
{
  delete_t_pack(pack);
}

bool
t_pack_const(t_pack *pack, char *msg)
{
  if (!msg || !pack)
    return (false);
  ZERO_MEM(pack);

  if (!(pack->string = strdup(msg)))
    return (TRACE("strdup() failed\n"), false);

  pack->size = strlen(msg);

  return (true);
}

t_pack
*new_t_pack(char *msg)
{
  t_pack        *pack;

  pack = malloc(sizeof(*pack));
  if (!pack)
    return (NULL);

  if (!t_pack_const(pack, msg))
    return (t_pack_dest(pack), NULL);

  return (pack);
}
