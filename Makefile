RM		= rm -f
CC		= gcc

NAME		= ipcat

CFLAGS		+= -W -Wall -Werror -Wextra -O3
CFLAGS		+= -ansi -pedantic
CFLAGS		+= -I.

SRC		= main.c \
		  strtowordtab.c \
		  itoa.c

OBJ		= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		clean fclean all
