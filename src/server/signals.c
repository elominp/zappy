/*
** signals.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Jun 26 14:44:44 2016 querat_g
** Last update Sun Jun 26 14:44:45 2016 querat_g
*/

#include <signal.h>
#include "server.h"
#include "macros.h"

static t_serv   *g_servptr;

/*
** I don't like using exit(), but for some reason
** signals make select() buggy and tamper with
** the main server loop (causing blocking reads)
*/
static void     sighandler(int UNUSED(sig))
{
  if (!g_servptr)
    return ;

  ERR(YELLOW"signal caught: exiting properly !\n"WHITE);
  t_serv_dest(g_servptr);
  g_servptr = NULL;

  exit(1);
  g_servptr->exit = true;
}

static void
sigpipe(int UNUSED(sig))
{
  (void)sig;
  ERR(PINK"SigPipe !\n"WHITE);
}

bool            signals(t_serv *s)
{
  if (!s)
    return (false);
  g_servptr = s;

  if (signal(SIGINT, &sighandler) == SIG_ERR ||
      signal(SIGQUIT, &sighandler) == SIG_ERR ||
      signal(SIGPIPE, &sigpipe) == SIG_ERR ||
      signal(SIGTERM, &sighandler) == SIG_ERR)
    return (perror("signal()"), false);

  return (true);
}
