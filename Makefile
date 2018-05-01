##
## EPITECH PROJECT, 2018
## PSU_2017_myftp
## File description:
## 
##

NAME_SRV	=	myftp

CC		=	gcc

CFLAGS		=	-Iinc -Wall -Wextra -pedantic

LDFLAGS		=

SRC_SRV		=	src/server/main.c		\
			src/server/useful.c		\
			src/server/handle_client.c	\
			src/server/ftp_cmd.c		\
			src/server/ftp_user.c		\
			src/server/ftp_pasv.c		\
			src/server/ftp_dir.c		\
			src/server/misc.c		\
			src/server/ftp_file.c		\
			src/server/socket.c

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

OBJ_SRV		=	$(SRC_SRV:.c=.o)

all:		$(NAME_SRV)

$(NAME_SRV):	$(OBJ_SRV)
			$(CC) $(CFLAGS) -o $(NAME_SRV) $(OBJ_SRV) $(LDFLAGS)

clean:
		rm -f $(OBJ_SRV)

fclean:		clean
		rm -f $(NAME_SRV)

re:		fclean all

.PHONY:		all clean fclean re
