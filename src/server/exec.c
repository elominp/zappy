/*
** exec.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu May 26 11:00:33 2016 querat_g
** Last update Sun Jun 26 15:08:59 2016 schmou_a
*/

#include "server.h"

static const t_cmdcor           g_cmdtoaifunc[] =
  {
    { "voir"       , &voir       , 7000   },
    { "avance"     , &avance     , 7000   },
    { "droite"     , &droite     , 7000   },
    { "gauche"     , &gauche     , 7000   },
    { "prend"      , &prend      , 7000   },
    { "pose"       , &pose       , 7000   },
    { "inventaire" , &inventaire , 7000   },
    { "expulse"    , &expulse    , 7000   },
    { "broadcast"  , &broadcast  , 7000   },
    { "connect_nbr", &connect_nbr, 0      },
    { "fork"       , &fork_ai    , 42000  },
    { "incantation", &incantation, 300000 },
    { NULL         , NULL        , 0      }
  };

static const t_cmdcor           g_cmdtographicfunc[] =
  {
    { "msz", &msz , 0xc },
    { "bct", &bct , 0x0 },
    { "mct", &mct , 0xf },
    { "tna", &tna , 0xf },
    { "ppo", &ppo , 0xe },
    { "plv", &plv , 0xe },
    { "pin", &pin , 0 },
    { "sgt", &sgt , 0 },
    { "sst", &sst , 0 },
    { NULL , NULL , 0 }
  };

static void
remove_line_feed(char *buf)
{
  int           i;

  i = 0;
  while (buf[i])
    ++i;
  if (i >= 1)
    buf[i - 1] = '\0';
  hex_dump(buf, strlen(buf));
}

static bool
exec_graphic_command(t_cli *c, t_msg *msg)
{
  int           i;

  for (i = 0; g_cmdtographicfunc[i].cmd && g_cmdtographicfunc[i].func; i++)
    {
      if (msg->command && !strcasecmp(msg->command,
                                      g_cmdtographicfunc[i].cmd))
        {
          g_cmdtographicfunc[i].func(c, msg);
          return (t_msg_dest(msg), true);
        }
    }
  suc(c);
  return (true);
}

bool
exec_ai_command(t_cli *c, t_msg *msg)
{
  int           i;

  for (i = 0; g_cmdtoaifunc[i].cmd && g_cmdtoaifunc[i].func; i++)
    {
      if (msg->command && !strcasecmp(msg->command, g_cmdtoaifunc[i].cmd))
        {
          g_cmdtoaifunc[i].func(c, msg);
          return (t_msg_dest(msg), true);
        }
    }

  return (true);
}

bool
push_command_into_queue(t_cli *c, t_msg *msg)
{
  if (!c->commands || !msg)
    return (false);
  if (list_len(c->commands) >= 10 && !c->is_graphic)
    return (true);

  if (!list_append(&c->commands, msg))
    return (TRACE("list_append() failed"), false);
  return (true);
}

/*
** Execute instantly graphical users commands
**
** Enqueue the AI's commands that will be executed after their defined
** execution time
*/
bool
exec_client_command(t_cli *c, char *buf)
{
  t_msg         msg;
  int           i;

  if (!buf)
    return (false);
  remove_line_feed(buf);
  if (!t_msg_const(&msg, buf))
    return (TRACE("t_msg_const() failed"), false);
  if (!c->team)
    return (try_join_team(c, msg.command), t_msg_dest(&msg), true);
  else if (c->is_graphic)
    exec_graphic_command(c, &msg);
  else
    {
      for (i = 0; g_cmdtoaifunc[i].cmd; ++i)
        if (!strcasecmp(g_cmdtoaifunc[i].cmd, msg.command))
          msg.exec_after = gettimeofday_ms() +
            (g_cmdtoaifunc[i].delay / (c->servptr->opt->time ?
                                       c->servptr->opt->time : 1));
      return (push_command_into_queue(c, memdup(&msg, sizeof(msg))));
    }
  return (t_msg_dest(&msg), true);
}
