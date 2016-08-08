##
## Makefile for  in /home/querat_g/tmp/PSU_2015_zappy
## 
## Made by querat_g
## Login   <querat_g@epitech.net>
## 
## Started on  Tue Jun  7 10:50:15 2016 querat_g
## Last update Sun Jun 26 22:43:11 2016 schmou_a
##

RED		=	"\033[1;31m"
GREEN		=	"\033[1;32m"
YELLOW		=	"\033[1;33m"
BROWN		=	"\033[0;33m"
BLUE		=	"\033[1;34m"
PINK		=	"\033[1;35m"
CYAN		=	"\033[1;36m"
WHITE		=	"\033[0m"
WWHITE		=	"\033[1;0m"

CC		=	gcc

CFLAGS		=	-W -Wall -Wextra -std=gnu11
CFLAGS		+=	-I./include/

LDFLAGS		=

# includes need to be evaluated before the all rule
default:		all

.c.o:
			@ `which echo` -e $(CYAN)"[compiling]"$(WHITE) $<
			@ $(CC) $< $(CFLAGS) -c -o $@

include 		lib.mk
include 		server.mk
include 		client.mk

all:			$(LIBOBJS) $(SERVNAME) $(CLINAME) $(GUINAME)

clean:
			rm -f $(CLIOBJS) $(SERVOBJS) $(LIBOBJS)

fclean:			clean
			rm -f $(CLINAME) $(SERVNAME)
re:			fclean all

tags:			# Needed for emacs quick-jump
			find . -name "*.[ch]" | etags -


prod:			all

debug:			CFLAGS += -D__DEBUG__ -g -Wno-unused
debug:			all tags
debugre:		fclean debug

check-syntax:		# flymake
			gcc -o /tmp/nul -S $(CHK_SOURCES) $(CFLAGS) -Wno-unused

.PHONY:			all clean fclean re \
			tags debug debugre .c.o \
			prod default check-syntax \

