/*
** usage.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Jun 10 11:29:18 2016 querat_g
** Last update Fri Jun 10 11:29:31 2016 querat_g
*/

#include <stdio.h>

void
usage(char **av)
{
  printf("usage: %s -p port "
         "-n team1 [team2 ...] "
         "[-x width] [-y height] "
         "[-c max_clients] "
         "[-t delay]"
         "\n",
         av[0]);
}
