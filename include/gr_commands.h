/*
** gr_commands.h for  in /home/schmou/SysUnix/PSU_2015_zappy/include
**
** Made by schmou_a
** Login   <schmou@epitech.net>
**
** Started on  Tue Jun 14 14:37:36 2016 schmou_a
// Last update Thu Jun 23 12:29:55 2016 querat_g
*/

#ifndef GR_COMMANDS_H_
# define GR_COMMANDS_H_

struct s_egg;
typedef struct s_egg t_egg;
//======== Response to graphic client input ========

bool            msz(t_cli*, t_msg*);
bool            bct(t_cli*, t_msg*);
bool            mct(t_cli*, t_msg*);
bool            tna(t_cli*, t_msg*);
bool            ppo(t_cli*, t_msg*);
bool            plv(t_cli*, t_msg*);
bool            pin(t_cli*, t_msg*);
bool            sgt(t_cli*, t_msg*);
bool            sst(t_cli*, t_msg*);

//======== When an event occurs and we have to ==========
//========    inform the graphical clients     ==========

bool            pnw(t_cli*);
bool            pex(t_cli*);
bool            pbc(t_cli*, char const *);
bool            pic(t_cli*);
bool            pie(t_cli*, int success);
bool            pfk(t_cli*);
bool            pdr(t_cli*, t_rsrc dropped);
bool            pgt(t_cli*, t_rsrc taken);
bool            pdi(t_cli*);
bool            eht(t_cli*);
bool            ebo(t_cli*);
bool            edi(t_hash*, t_egg*);
bool            seg(t_cli*);
bool            smg(t_cli*, char*);
bool            suc(t_cli*);
bool            spb(t_cli*);
bool            enw(t_cli*);

#endif
