/*
** rfc1459_cmd_parser.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 13:56:01 2016 querat_g
** Last update Thu Jun 16 12:25:09 2016 querat_g
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <sys/types.h>
#include <regex.h>

#include "myirc.h"
#include "macros.h"
#include "list.h"
#include "my_regex.h"

/*
** <command> ::= <letter> { <letter> } | <number> <number> <number>
*/
bool
lex_command(char **command, char **str)
{
  if (regex_get_and_skip_match(COMMAND_REG, str, command) <= 0)
    return (TRACE("invalid <command>\n"), false);
  return (true);
}

bool
t_msg_dest(t_msg *msg)
{
  if (msg->raw)
    free(msg->raw);
  if (msg->params)
    msg->params->destruct(&msg->params, &free);
  if (msg->command)
    free(msg->command);

  ZERO_MEM(msg);
  return (true);
}

bool
lex_msg(t_msg *msg, char *str)
{
  if (!lex_command(&msg->command, &str))
    return (t_msg_dest(msg), false);
  while (*str && strncmp(str, "\n", 1))
    if (!lex_param(&msg->params, &str))
      return (t_msg_dest(msg), false);
#ifdef __DEBUG__
  ERR("cmd: '%s'\n", msg->command);
  ERR("parameters:\n");
  msg->params->for_each(msg->params, &print_param, NULL);
  ERR("[[end of parameters]]\n");
  ERR("str left from current pos: '%s'\n", str);
#endif
  return (true);
}

bool
t_msg_const(t_msg *msg, char *str)
{
  ZERO_MEM(msg);
  if (!(msg->raw = strdup(str)))
    return (perror("strdup()"), false);
  if (!(msg->params = new_list()))
    return (TRACE("new_list() failed"), free(msg->raw), false);
  if (!lex_msg(msg, str))
    return (t_msg_dest(msg), false);
  return (true);
}
