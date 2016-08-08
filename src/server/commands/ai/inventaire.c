/*
** inventaire.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Jun 26 14:45:36 2016 querat_g
** Last update Sun Jun 26 14:45:36 2016 querat_g
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "macros.h"

static char     *g_buffer = NULL;
static off_t    g_off = 0;
static bool     g_is_first_print = false;

static bool
print_to_buffer(char const *str)
{
  int           ret;

  ret = snprintf((g_buffer + g_off), (INVENTAIRE_BUF_SIZE - g_off),
                 "%s", str);
  if (ret < 0)
    return (TRACE("snprintf() failed"), false);
  g_off += ret;
  return (true);
}

static bool
print_res(t_cli *c, char const *res)
{
  t_item        *itemstack;
  char          buf[64];

  print_to_buffer(res);
  print_to_buffer(" ");
  if (!(itemstack = ht_get_entry(c->inventory, res, strlen(res))))
    {
      print_to_buffer("0");
      return (true);
    }
  snprintf(buf, sizeof(buf), "%zu", itemstack->amount);
  print_to_buffer(buf);
  return (true);
}

static bool
print_inv(t_cli *c)
{
  print_res(c, "nourriture");
  print_to_buffer(", ");
  print_res(c, "linemate");
  print_to_buffer(", ");
  print_res(c, "deraumere");
  print_to_buffer(", ");
  print_res(c, "sibur");
  print_to_buffer(", ");
  print_res(c, "mendiane");
  print_to_buffer(", ");
  print_res(c, "phiras");
  print_to_buffer(", ");
  print_res(c, "thystame");
  return (true);
}

bool
inventaire(t_cli *c, t_msg UNUSED(*msg))
{
  ERR(PINK"[%s], client %d from team '%s'\n"WHITE,
  __func__, c->sock.fd, c->team->name);

  g_buffer = malloc(INVENTAIRE_BUF_SIZE);
  g_off = 0;
  g_is_first_print = true;
  if (!g_buffer)
    return (perror("malloc()"), false);

  print_to_buffer("{");
  print_inv(c);
  print_to_buffer("}\n");
  enqueue_msg(c, g_buffer);
  free(g_buffer);
  return (true);
}
