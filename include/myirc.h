/*
** myirc.h for  in /home/querat_g/tmp/PSU_2015_myirc
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon May 16 11:04:50 2016 querat_g
// Last update Mon Jun 20 17:19:00 2016 querat_g
*/

#ifndef MYIRC_H_
# define MYIRC_H_

# include <sys/types.h>
# include <stdbool.h>
# include <assert.h>
# include <stdio.h>
# include "macros.h"
# include "list.h"

typedef struct          s_msg
{
  char                  *raw;
  char                  *command;
  t_list                *params;
  int64_t               exec_after;
}                       t_msg;

void            hex_dump(char *buf, size_t size);

int             regex_does_match(char *regstr, char *str);
int             regex_skip_match(char *regstr, char **str);
int             regex_get_match(char *regstr, char *str, char **res);
int             regex_get_and_skip_match(char *regstr, char **str, char **res);

int             print_param(void *data, void *extradata);

int             to_space(char *str);
void            skip_one_space(char **str);
int             to_crlf(char *str);

bool            lex_param(t_list **params, char **str);

bool            t_msg_const(t_msg *msg, char *buf);
bool            t_msg_dest(t_msg *msg);

void            *memdup(void *src, size_t size);

void            delete_t_msg(void *voidmsg);

#endif
