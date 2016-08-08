/*
** stdin.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 21 14:40:30 2016 querat_g
** Last update Fri Jun  3 13:13:34 2016 querat_g
*/

#include <errno.h>
#include "server.h"

static t_status serv_getline(t_serv *s, char **cmd)
{
  size_t        sz;
  int           ret;

  sz = 0;
  errno = 0;
  ret = getline(cmd, &sz, stdin);
  if (ret < 0 && isatty(STDIN_FILENO))
    {
      s->exit = true;
      if (!errno)
        return (free(*cmd), ERR(RED"Ctrl-d, Exiting...\n"WHITE), NO_ACTION);
      return (perror("getline()"), ERROR);
    }
  return (ACTION_OK);
}

t_status        process_serverside_actions(t_serv *s)
{
  char          *cmd;
  int           ret;

  cmd = NULL;
  if (FD_ISSET(STDIN_FILENO, &s->fdset_read))
    {
      ret = serv_getline(s, &cmd);
      if (ret != ACTION_OK)
        return (ret);

      if (!strcmp(cmd, "quit\n") || !strcmp(cmd, "exit\n"))
        {
          ERR("exiting ...\n");
          s->exit = true;
          return (free(cmd), ACTION_OK);
        }
      if (!(*cmd) || (*cmd) == '\n')
        return (free(cmd), NO_ACTION);
      return (ERR(YELLOW"unknown command '%s'\n"WHITE"$>", cmd),
              free(cmd), NO_ACTION);
    }
  return (free(cmd), NO_ACTION);
}
