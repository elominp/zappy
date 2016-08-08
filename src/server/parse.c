/*
** parse.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed May 25 09:16:46 2016 querat_g
** Last update Tue Jun 21 12:13:03 2016 querat_g
*/

#include "server.h"

static int
len_to_crlf(char *buf)
{
  int           i;

  i = 0;
  while (buf[i])
    {
      if (!strncmp(&buf[i], "\n", 1))
        return (i + 1);
      ++i;
    }
  return (-1);
}

static void
parse_and_exec_client_command(void *data)
{
  t_cli         *cli;
  char          buf[CIRCULAR_BUF_SIZE + 1];
  int           len;

  if (!(cli = data))
      return ;

  while (cli->buffer.content > 0)
    {
      *buf = 0;
      cli->buffer.peek(&cli->buffer, buf, CIRCULAR_BUF_SIZE);
      if ((len = len_to_crlf(buf)) < 0)
        return ;
      ERR("client %d's command is ready ! '%s'", cli->sock.fd, buf);
      cli->buffer.read(&cli->buffer, buf, len);
      exec_client_command(cli, buf);
    }
}

void
parse_and_exec_clients_commands(t_serv *s)
{
  ht_foreach(s->clients, &parse_and_exec_client_command);
}
