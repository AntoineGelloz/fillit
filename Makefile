# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agelloz <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 11:12:29 by agelloz           #+#    #+#              #
#    Updated: 2019/05/12 20:24:50 by ptroger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = fillit
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBH = libft/includes
LIBA = libft/libft.a

SRC = fillit.c get_next_line.c parse.c parse_check.c parse_format.c \
	  free.c map.c solve.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBA) $(OBJ) Makefile
	$(CC) $(CFLAGS) -I$(LIBH) -Llibft -lft -o $(NAME) -g3 $(OBJ)

$(LIBA):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBH) -o $@ -c $< -g3

clean:
	make -Clibft fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
