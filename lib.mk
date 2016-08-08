##
## lib.mk for  in /home/querat_g/tmp/PSU_2015_zappy
## 
## Made by querat_g
## Login   <querat_g@epitech.net>
## 
## Started on  Tue Jun  7 12:39:21 2016 querat_g
## Last update Sat Jun 11 11:44:12 2016 querat_g
##


LIBSRCS		=	src/lib/list/list_len.c \
			src/lib/list/list_destruct.c \
			src/lib/list/list_remove_if.c \
			src/lib/list/list_prepend.c \
			src/lib/list/list_append.c \
			src/lib/list/list_insert.c \
			src/lib/list/list_cmp.c \
			src/lib/list/list_init.c \
			src/lib/list/list_for_each.c \
			src/lib/list/list_rm.c \
			src/lib/list/list_print.c \
			src/lib/list/list_count_if.c \
			\
			src/lib/circ/circ_print.c \
			src/lib/circ/circ_const.c \
			src/lib/circ/circ_dest.c \
			src/lib/circ/circ_read.c \
			src/lib/circ/circ_write.c \
			src/lib/circ/circ_flush.c \
			\
			src/lib/hash/ht_add_entry.c \
			src/lib/hash/ht_get_entry.c \
			src/lib/hash/ht_foreach.c \
			src/lib/hash/ht_key_cmp.c \
			src/lib/hash/ht_init.c \
			src/lib/hash/ht_free.c \
			src/lib/hash/ht_hash.c \
			src/lib/hash/ht_count.c \
			src/lib/hash/ht_count_if.c \
			src/lib/hash/ht_rm_entry.c \
			src/lib/hash/ht_print.c \
			\
			src/lib/rfc_parser/lex_param.c \
			src/lib/rfc_parser/offset.c \
			src/lib/rfc_parser/print.c \
			src/lib/rfc_parser/rfc1459_cmd_parser.c \
			\
			src/lib/hex_dump.c \
			src/lib/memdup.c \
			\
			src/lib/regex.c \
			\
			src/lib/zappy.c \

LIBOBJS 	=	$(LIBSRCS:.c=.o)
