/*
** circularbuffer.h for  in /home/querat_g/tmp/circ_buffer
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue May 17 10:12:25 2016 querat_g
// Last update Sun May 22 14:07:46 2016 querat_g
*/

#ifndef CIRCULARBUFFER_H_
# define CIRCULARBUFFER_H_

# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <ctype.h>
# include <unistd.h>
# include <stdlib.h>

# include "macros.h"

# define CIRC(x, y)             (((y) % x->size))

# define CIRC_INC_HEAD(x)       x->head = (CIRC(x, x->head + 1))
# define CIRC_INC_TAIL(x)       x->tail = (CIRC(x, x->tail + 1))

typedef struct s_circ   t_circ;

struct                  s_circ
{
  size_t                size;
  size_t                head;
  size_t                tail;
  size_t                content;
  char                  *buf;
  bool                  (*print)(t_circ *c);
  size_t                (*write)(t_circ *c, void *mem, size_t size);
  size_t                (*overwrite)(t_circ *c, void *mem, size_t size);
  size_t                (*read)(t_circ *c, void *buf, size_t size);
  size_t                (*peek)(t_circ *c, void *buf, size_t size);
  void                  (*clear)(t_circ *c);
};

bool                    t_circ_const(t_circ *c, size_t size);
bool                    t_circ_dest(t_circ *c);
t_circ                  *new_t_circ(size_t size);
t_circ                  *delete_t_circ(t_circ **c);

bool                    t_circ_print(t_circ *c);
size_t                  t_circ_write(t_circ *c, void *mem, size_t size);
size_t                  t_circ_read(t_circ *c, void *buf, size_t size);
size_t                  t_circ_peek(t_circ *c, void *buf, size_t size);
void                    t_circ_clear(t_circ *c);
size_t                  t_circ_overwrite(t_circ *c, void *mem, size_t size);

#endif
