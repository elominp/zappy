##
## client.mk for  in /home/querat_g/tmp/PSU_2015_zappy
## 
## Made by querat_g
## Login   <querat_g@epitech.net>
## 
## Started on  Tue Jun  7 11:47:42 2016 querat_g
## Last update Sun Jun 26 09:40:01 2016 querat_g
##

CLINAME		=	./zappy_ai

CLISRCS		=	./src/client_ia/IA_launcher.sh \

$(CLINAME):		
		@ `which echo` -e $(BROWN)[installing]$(WHITE) $(CLINAME)
		@ cp $(CLISRCS) $(CLINAME)
		@ chmod 755 $(CLINAME) 
