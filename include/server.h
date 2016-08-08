/*
** server.h for  in /home/querat_g/tmp/PSU_2015_totallyNotMyIrc/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue May 17 09:20:00 2016 querat_g
** Last update Sun Jun 26 15:00:19 2016 schmou_a
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <netdb.h>
# include "list.h"
# include "hash.h"
# include "myirc.h"
# include "macros.h"
# include "circularbuffer.h"

# include "zappy.h"
# include "client.h"
# include "map.h"
# include "t_opt.h"
# include "t_pack.h"
# include "ai_commands.h"
# include "gr_commands.h"

// # ifdef __DEBUG__
// #  define WELCOME               "VIENBENUE\n"
// # else
#  define WELCOME               "BIENVENUE\n"
// # endif

# define GRAPHIC_TEAM_NAME      "GRAPHIC"

# define MAX_CLIENTS            2048
# define SELECT_TIMEOUT_MS      100
# define SELECT_TIMEOUT         (SELECT_TIMEOUT_MS * 1000)
# define MAX_NICK               9
# define MAX_MSG                512
# define CLI_HASH_BUCKETS       10
# define CIRCULAR_BUF_SIZE      0x2000

/*
** Less tick rate in debug mode
*/
# ifndef __DEBUG__
#  define TICK_INTERVAL         (10 * 1000)
# else
#  define TICK_INTERVAL         (100 * 1000)
# endif

# define ISVALIDFD(x)           (x > 0)

typedef enum            e_status
  {
    UNDEFINED           = 0,
    DISCONNECTED,
    ERROR,
    NO_ACTION,
    ACTION_OK
  }                     t_status;

typedef struct          s_egg
{
    int64_t             id;
    int64_t             x;
    int64_t             y;
    float               life_time;
}                       t_egg;

typedef struct          s_team
{
  char                  *name;
  uint64_t              nb_members;
  uint64_t              nb_slots;
  t_hash                *eggs;
  t_list                *eggs_sorted;
}                       t_team;

typedef struct  s_ded
{
    t_egg       *egg;
    t_team      *team;
}               t_ded;

typedef struct          s_serv
{
  t_opt                 *opt;
  int			connected_clients;
  uint16_t              port;
  t_sock                connectsock;
  bool                  exit;
  fd_set                fdset_read;
  fd_set                fdset_write;
  int                   maxfd;
  t_hash                *clients;
  t_map                 map;
  t_list                *teams;
  int64_t               current_time;
  int64_t               prev_egg_id;
}                       t_serv;

typedef struct          s_cmdcor
{
  char                  *cmd;
  bool                  (*func)(t_cli *, t_msg *);
  /*
  ** delay, in milliseconds
  */
  int                   delay;
}                       t_cmdcor;

int             main(int ac, char **av);
bool            t_serv_dest(t_serv *s);
bool            t_serv_const(t_serv *s, t_opt *opt);
bool            signals(t_serv *s);
int             my_select(t_serv *s);
bool            try_accept(t_serv *s);
t_status        process_serverside_actions(t_serv *s);
void            process_clients_input(t_serv *s);
bool            kick_client(t_serv *s, int id);
void            parse_and_exec_clients_commands(t_serv *s);
bool            exec_client_command(t_cli *c, char *buf);
bool            enqueue_msg(t_cli *c, char *msg);
void            process_output_queue(void *data);
void            process_clients_output(t_serv *s);

bool            is_in_list(t_list *l, char *str);

void            t_item_dest(t_item *item);
void            t_item_const(t_item *item, enum e_rsrc type, uint32_t amount);
t_item          *new_t_item(enum e_rsrc type, size_t amount);

bool            t_team_dest(t_team *t);
bool            t_team_const(t_team *t, char *name);
t_team          *new_t_team(char *name);
void            delete_t_team(void *team);

bool            try_join_team(t_cli *c, char const *team);

int64_t         my_clock(void);
int64_t         gettimeofday_ms(void);

bool            exec_ai_command(t_cli *c, t_msg *msg);
void            circular(t_map *map, t_coord *c);
int             decrement_food(t_serv *serv);

bool            tile_meets_prerequisites(t_serv *s, t_coord c, int level);
int             count_players_at(t_serv *s, t_coord *c, int level);
int             upgrade_players_at(t_serv *s, t_coord *c, int level);
int             remove_incantation_ressources_from_map(t_serv *serv,
                                                       t_coord *c,
                                                       int level);
int             populate_map(t_map *m);
bool            send_ppo(t_cli *c);
bool            is_ready_to_read(int fd, unsigned int timeout);
bool            is_ready_to_write(int fd, unsigned int timeout);
int             same_level_at(t_serv *s, t_coord *c, int level);

#endif
