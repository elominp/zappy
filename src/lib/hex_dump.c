/*
** hex_dump.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu May 26 11:35:31 2016 querat_g
** Last update Thu May 26 12:19:25 2016 querat_g
*/

#include <ctype.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static void             dump_hex_line(char *buf, size_t lft)
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
      if (i && !(i % 4))
        printf(" ");

      printf("  ");
      ++i;
    }
    printf("  ");
}

void                    hex_dump(char *buf, size_t size)
{
  size_t	i;

  i = 0;
  if (!buf || !size)
    return ;
  while (i < size)
    {
      dump_hex_line(&buf[i], (size - i));
      dump_char_line(&buf[i], (size - i));
      printf("\n");
      i += 16;
    }
}
