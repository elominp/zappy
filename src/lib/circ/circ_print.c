/*
** circ_print.c for  in /home/querat_g/tmp/circ_buffer
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue May 17 18:30:55 2016 querat_g
** Last update Tue May 17 18:38:31 2016 querat_g
*/

#include "circularbuffer.h"

static void             dump_char_line(char *buf, size_t lft)
{
  size_t	i;

  i = 0;
  while (i < 16 && i < lft)
    {
      printf("%c", isprint(buf[i]) ? buf[i] : '.');
      ++i;
    }
  while (i < 16)
    {
      printf(" ");
      ++i;
    }
}

static void             dump_hex_line(char *buf, size_t lft, t_circ UNUSED(*c))
{
  size_t	i;

  i = 0;
  while (i < 16 && i < lft)
    {
      if (i && !(i % 4))
	putchar(' ');
      printf("%x", (unsigned int)(((buf[i] & 0xF0) >> 4)));
      printf("%x", (unsigned int)(buf[i] & 0x0F));
      ++i;
    }
  while (i < 16)
    {
      if (i && !(i % 2))
	printf(" ");
      printf("  ");
      ++i;
    }
    printf("  ");
}

static void             hex_dump(char *buf, size_t size, t_circ *c)
{
  size_t	i;

  i = 0;
  if (!buf || !size)
    return ;
  while (i < size)
    {
      dump_hex_line(&buf[i], (size - i), c);
      dump_char_line(&buf[i], (size - i));
      printf("\n");
      i += 16;
    }
}

bool                    t_circ_print(t_circ *c)
{
  if (!c || !c->buf)
    return (TRACE("NULL pointer exception\n"), false);
  hex_dump(c->buf, c->size, c);
  return (true);
}
