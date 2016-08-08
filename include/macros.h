/*
** macros.h for  in /home/querat_g/tmp/PSU_2015_myirc
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed May 18 09:29:18 2016 querat_g
// Last update Wed Jun 22 12:30:45 2016 querat_g
*/

#ifndef MACROS_H_
# define MACROS_H_

# include <assert.h>
# include <string.h>
# include <stdio.h>

# define FUNC           __func__
# define LINE           __LINE__

# define _F(f)          stderr, f". [@%s()]""\n"

# ifdef __DEBUG___
#  define DEBUG(f, ...) fprintf(stderr, f, FUNC ##__VA_ARGS__)
#  define ASSERT(x)     assert(x)
# else
#  define DEBUG(...)    {}
#  define ASSERT(x)     {}
# endif

# define TRACE(f, ...)  fprintf(_F(f), ##__VA_ARGS__, FUNC)
# define ERR(...)      fprintf(stderr, __VA_ARGS__)

# define UNUSED(x)      x __attribute__ ((unused))
# define ZERO_MEM(x)    memset(x, '\0', sizeof(*x))
# define SAFE_STR(x)    x, (sizeof(x) - 1)

# define FAILS(x)       ((x) < 0)

/*
** Colors
*/
# define RED                    "\033[1;31m"
# define GREEN                  "\033[1;32m"
# define YELLOW                 "\033[1;33m"
# define BROWN                  "\033[0;33m"
# define BLUE                   "\033[1;34m"
# define PINK                   "\033[1;35m"
# define CYAN                   "\033[1;36m"
# define WHITE                  "\033[0m"
# define WWHITE                 "\033[1;0m"
# define DRED                    "\033[0;31m"
# define DGREEN                  "\033[0;32m"
# define DBLUE                   "\033[0;34m"
# define DPINK                   "\033[0;35m"
# define DCYAN                   "\033[0;36m"

#endif
