##
## gui.mk for  in /home/querat_g/tmp/PSU_2015_zappy
## 
## Made by querat_g
## Login   <querat_g@epitech.net>
## 
## Started on  Tue Jun  7 12:09:37 2016 querat_g
## Last update Thu Jun  9 09:44:29 2016 querat_g
##

GUINAME		=	./zappy_gui

GUISRCS		=	./src/gui/main.c \

GUIOBJS 	=	$(GUISRCS:.c=.o)

GUI_LDFLAGS	=	

$(GUINAME):		$(GUIOBJS)
			@ `which echo` -e $(GREEN)[linking]$(WHITE) $(GUINAME)
			@ gcc -o $(GUINAME) \
			$(GUI_LDFLAGS) $(LDFLAGS) \
			$(GUIOBJS) $(LIBOBJS)
