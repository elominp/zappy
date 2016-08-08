/*
** ai_commands.h for  in /home/querat_g/tmp/PSU_2015_zappy/src/server
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Jun 14 10:33:42 2016 querat_g
// Last update Thu Jun 23 12:29:37 2016 querat_g
*/

#ifndef AI_COMMANDS_H_
# define AI_COMMANDS_H_

/*
** 262 Ko
*/
# define VOIR_BUFFER_SIZE       (1 << 18)
# define INVENTAIRE_BUF_SIZE    (8192)

bool            avance(t_cli*, t_msg*);
bool            droite(t_cli*, t_msg*);
bool            gauche(t_cli*, t_msg*);
bool            voir(t_cli*, t_msg*);
bool            prend(t_cli*, t_msg*);
bool            pose(t_cli*, t_msg*);
bool            inventaire(t_cli*, t_msg*);
bool            expulse(t_cli*, t_msg*);
bool            connect_nbr(t_cli*, t_msg*);
bool            broadcast(t_cli*, t_msg*);

bool            incantation(t_cli*, t_msg*);
bool            fork_ai(t_cli*, t_msg*);

int             count_players_on_tile(t_cli *c, t_coord pos);
void            print_matrix(t_coord mat[9]);
void            print_distances(double d[9]);
void            build_distances(t_coord diff[9], double *dist);
int             get_min_distance_index(double *distances);
int             convert_index_according_to_direction(t_cli *c, t_dir dir,
                                                     int  min_index);
bool            send_broadcast(t_cli *c, char const *msg, int min_index);

#endif
