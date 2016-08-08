/*
** print.c for  in /home/querat_g/tmp/PSU_2015_zappy/src/server/commands/ai
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Jun 16 18:09:21 2016 querat_g
** Last update Thu Jun 16 18:23:46 2016 querat_g
*/

#include "server.h"
#include "macros.h"

/*
** My brain ! it is melting !
*/
void
print_matrix(t_coord mat[9])
{

  ERR(GREEN"(%ld;%ld)"WHITE, mat[2].x, mat[2].y);
  ERR(GREEN"(%ld;%ld)"WHITE, mat[1].x, mat[1].y);
  ERR(GREEN"(%ld;%ld)"WHITE, mat[8].x, mat[8].y);
  ERR("\n");

  ERR(GREEN"(%ld;%ld)"WHITE, mat[3].x, mat[3].y);
  ERR(GREEN"(%ld;%ld)"WHITE, mat[0].x, mat[0].y);
  ERR(GREEN"(%ld;%ld)"WHITE, mat[7].x, mat[7].y);
  ERR("\n");

  ERR(GREEN"(%ld;%ld)"WHITE, mat[4].x, mat[4].y);
  ERR(GREEN"(%ld;%ld)"WHITE, mat[5].x, mat[5].y);
  ERR(GREEN"(%ld;%ld)"WHITE, mat[6].x, mat[6].y);
  ERR("\n");
}

void
print_distances(double d[9])
{

  ERR(BROWN"%f %f %f\n"WHITE, d[2], d[1], d[8]);
  ERR(BROWN"%f %f %f\n"WHITE, d[3], d[0], d[7]);
  ERR(BROWN"%f %f %f\n"WHITE, d[4], d[5], d[6]);
}
