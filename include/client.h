/*
** client.h for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 10:56:49 2016 querat_g
// Last update Sun Jun 26 14:40:51 2016 querat_g
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <sys/time.h>

struct                  s_serv;
typedef struct   s_serv t_serv;

struct                  s_team;
typedef struct   s_team t_team;

extern char const       *g_direction_str[];

typedef enum            e_dir
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  }                     t_dir;

typedef struct          s_sock
{
  struct sockaddr_in    sin;
  int                   fd;
}                       t_sock;

typedef struct          s_cli
{
  /*
  ** Networking members
  */
  t_sock                sock;
  char                  *ip;
  t_list                *outqueue;
  t_circ                buffer;

  /*
  ** Zappy related client members
  */
  bool                  is_graphic;
  //char                  *team;
  t_team                *team;
  enum e_dir            direction;
  t_hash                *inventory;
  int                   level;
  int64_t               x_pos;
  int64_t               y_pos;
  float                 food;

  t_list                *commands;
  /*
  ** Not the cleanest, but i need to be able to access it in foreach'es
  */
  struct s_serv         *servptr;
}                       t_cli;

bool            t_cli_const(t_cli *c, t_serv *s);
bool            t_cli_dest(t_cli *c);
t_cli           *new_t_cli(t_serv *s);
t_cli           *delete_t_cli(t_cli *cli);
void            delete_t_cli_hook(void *c);

char const      *get_direction_str(enum e_dir direction);

int             take_from_client(t_cli *c, enum e_rsrc type, int quantity);
int             give_to_client(t_cli *c, enum e_rsrc type, int quantity);

int             to_graphical_dir(enum e_dir dir);
void            init_cli_vars(t_cli *c, t_serv *s);

#endif
