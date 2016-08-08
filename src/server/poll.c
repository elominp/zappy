/*
** poll.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri May 20 11:18:17 2016 querat_g
** Last update Sat Jun 25 10:51:57 2016 querat_g
*/

#include <poll.h>
#include <stdio.h>
#include <stdbool.h>

bool            is_ready_to_read(int fd, unsigned int timeout)
{
  int           ret;
  struct pollfd poll_;

  poll_.fd      = fd;
  poll_.events  = POLLIN;
  poll_.revents = 0;

  if ((ret = poll(&poll_, 1, timeout)) < 0) {
    perror("poll()");
    return (false);
  }

  return ((ret && (poll_.revents & POLLIN)) ? true : false);
}

bool            is_ready_to_write(int fd, unsigned int timeout)
{
  int           ret;
  struct pollfd poll_;

  poll_.fd      = fd;
  poll_.events  = POLLOUT;
  poll_.revents = 0;

  if ((ret = poll(&poll_, 1, timeout)) < 0)
    {
      perror("poll()");
      return (false);
    }

  return ((ret && (poll_.revents & POLLOUT)) ? true : false);
}
