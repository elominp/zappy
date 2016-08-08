/*
** main.c for  in /home/querat_g/tmp/test
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 27 10:01:36 2016 querat_g
** Last update Mon Jun 20 17:10:39 2016 querat_g
*/

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>
#include "macros.h"

static int64_t
usec_to_ms(suseconds_t usec)
{
  return (usec / 1000);
}

static int64_t
sec_to_ms(suseconds_t usec)
{
  return (usec * 1000);
}

int64_t
my_clock()
{
  static struct timeval then = {0, 0};
  struct timeval        now;
  int64_t               now_ms;
  int64_t               then_ms;

  if (!then.tv_sec && !then.tv_usec && gettimeofday(&then, NULL) < 0)
    return (perror("gettimeofday()"), -1);
  if (gettimeofday(&now, NULL) < 0)
    return (perror("gettimeofday()"), -1);
  then_ms = (sec_to_ms(then.tv_sec) + usec_to_ms(then.tv_usec));
  now_ms  = (sec_to_ms(now.tv_sec) + usec_to_ms(now.tv_usec));
  memcpy(&then, &now, sizeof(then));
  return (now_ms - then_ms);
}

int64_t
gettimeofday_ms()
{
  struct timeval        now;
  int64_t               ret;

  if (gettimeofday(&now, NULL) < 0)
    return (perror("gettimeofday()"), -1);
  ret = sec_to_ms(now.tv_sec) + usec_to_ms(now.tv_usec);
  return (ret);
}
