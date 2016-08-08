##
## server.dep for  in /home/querat_g/tmp/PSU_2015_zappy
## 
## Made by querat_g
## Login   <querat_g@epitech.net>
## 
## Started on  Tue Jun  7 10:52:54 2016 querat_g
## Last update Sun Jun 26 14:41:24 2016 querat_g
##

SERVNAME	=	./zappy_server

SERVSRCS	=	src/server/main.c \
			src/server/t_serv.c \
			src/server/t_pack.c \
			src/server/t_team.c \
			src/server/poll.c \
			src/server/signals.c \
			src/server/select.c \
			src/server/accept.c \
			src/server/stdin.c \
			src/server/client_input.c \
			src/server/kick.c \
			src/server/parse.c \
			src/server/exec.c \
			src/server/enqueue_msg.c \
			src/server/process_output.c \
			src/server/clock.c \
			src/server/circular.c \
			src/server/decrement_food.c \
			src/server/populate_map.c \
			src/server/direction.c \
			\
			src/server/client/t_cli.c \
			src/server/client/init_vars.c \
			src/server/client/take_from_client.c \
			\
			src/server/t_opt/usage.c \
			src/server/t_opt/parse_av.c \
			src/server/t_opt/t_opt.c \
			src/server/t_opt/t_opt_dump.c \
			src/server/t_opt/is_in_list.c \
			\
			src/server/t_map/t_map.c \
			src/server/t_map/add_item.c \
			src/server/t_map/take_item.c \
			src/server/t_map/make_coord.c \
			src/server/t_map/dump_map.c \
			src/server/t_map/at.c \
			\
			src/server/t_item/t_item.c \
			\
			src/server/commands/try_join_team.c \
			\
			src/server/commands/ai/avance.c \
			src/server/commands/ai/droite.c \
			src/server/commands/ai/gauche.c \
			src/server/commands/ai/voir.c \
			src/server/commands/ai/inventaire.c \
			src/server/commands/ai/prend.c \
			src/server/commands/ai/pose.c \
			src/server/commands/ai/expulse.c \
			\
			src/server/commands/ai/broadcast.c \
			src/server/commands/ai/broadcast/print.c \
			src/server/commands/ai/broadcast/build_distances.c \
			src/server/commands/ai/broadcast/min.c \
			src/server/commands/ai/broadcast/convert_direction.c \
			src/server/commands/ai/broadcast/send.c \
			\
			src/server/commands/ai/incantation/res_prerequisites.c \
			src/server/commands/ai/incantation/upgrade_players.c \
			src/server/commands/ai/incantation/count_players.c \
			\
			src/server/commands/ai/incantation.c \
			src/server/commands/ai/fork.c \
			src/server/commands/ai/connect_nbr.c \
			src/server/commands/ai/players_on_tile.c \
			\
			src/server/commands/graphic/responses/bct.c \
			src/server/commands/graphic/responses/mct.c \
			src/server/commands/graphic/responses/msz.c \
			src/server/commands/graphic/responses/pin.c \
			src/server/commands/graphic/responses/plv.c \
			src/server/commands/graphic/responses/ppo.c \
			src/server/commands/graphic/responses/sgt.c \
			src/server/commands/graphic/responses/sst.c \
			src/server/commands/graphic/responses/tna.c \
			\
			src/server/commands/graphic/events/pnw.c \
			src/server/commands/graphic/events/pex.c \
			src/server/commands/graphic/events/pbc.c \
			src/server/commands/graphic/events/pic.c \
			src/server/commands/graphic/events/pie.c \
			src/server/commands/graphic/events/pfk.c \
			src/server/commands/graphic/events/pdr.c \
			src/server/commands/graphic/events/pgt.c \
			src/server/commands/graphic/events/pdi.c \
			src/server/commands/graphic/events/enw.c \
			src/server/commands/graphic/events/eht.c \
			src/server/commands/graphic/events/ebo.c \
			src/server/commands/graphic/events/edi.c \
			src/server/commands/graphic/events/seg.c \
			src/server/commands/graphic/events/smg.c \
			src/server/commands/graphic/events/suc.c \
			src/server/commands/graphic/events/spb.c

SERV_LDFLAGS	=	-lm

SERVOBJS	=	$(SERVSRCS:.c=.o)

$(SERVNAME):		$(LIBOBJS) $(SERVDEPS) $(SERVOBJS)
			@ `which echo` -e $(GREEN)[linking]$(WHITE) $(SERVNAME)
			@ gcc -o $(SERVNAME)  \
			$(SERVOBJS) $(LIBOBJS) $(SERV_LDFLAGS) $(LDFLAGS)
