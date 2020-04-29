##
## Makefile for 42sh in /u/all/castel_a/cu/42sh/current
##
## Made by botton vivien
## Login   <botton_v@epitech.net>
##
## Started on  Tue Mar 30 18:15:50 2010 vivien botton
## Last update Sun May 23 23:33:47 2010 vivien botton
##

SERV	= serveur

SRCS_SERV	= serv/auth.c	\
		serv/cd.c	\
		serv/client.c	\
		serv/cmd.c	\
		serv/dir.c	\
		serv/divers_2.c	\
		serv/divers.c	\
		serv/file.c	\
		serv/file_edit.c\
		serv/functions.c\
		serv/init.c	\
		serv/list.c	\
		serv/main.c	\
		serv/port_pasv.c\
		serv/utils.c	\
		serv/dtp_op.c	\
		serv/control_op.c	\
		serv/xfunctions.c	\
		serv/xnet.c		\
		serv/xnet2.c

OBJS_SERV = $(SRCS_SERV:.c=.o)

CLIENT	= client

SRCS_CLIENT = cli/main.c	\
	cli/utils.c		\
	cli/cmd.c		\
	cli/control_op.c	\
	cli/file.c		\
	cli/functions.c		\
	cli/list.c		\
	cli/local.c		\
	cli/port_pasv.c		\
	cli/xfunctions.c	\
	cli/xnet.c		\
	cli/xnet2.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

CC	= clang

RM	= rm -f

CFLAGS	+= -ansi -Wall -Wextra -Wstrict-prototypes -pipe -O2

LIBS	= -lssl

all	: $(SERV) $(CLIENT)

$(SERV)	: $(OBJS_SERV)
	$(CC) -o $(SERV) $(OBJS_SERV) $(LIBS)

$(CLIENT) : $(OBJS_CLIENT)
	$(CC) -o $(CLIENT) $(OBJS_CLIENT)

clean	:
	$(RM) $(OBJS_SERV) $(OBJS_CLIENT)

fclean	: clean
	$(RM) $(SERV)
	$(RM) $(CLIENT)

re	: fclean all

#.c.o	:
#	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
