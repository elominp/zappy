/*
** print.c for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun May 29 14:04:25 2016 querat_g
** Last update Thu Jun  9 14:55:06 2016 querat_g
*/

#include <stdio.h>
#include "myirc.h"

int
print_param(void *data, void UNUSED(*extradata))
{
  ERR("%s\n", (char*)data);
  return (0);
}
