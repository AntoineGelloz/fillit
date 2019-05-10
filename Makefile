# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agelloz <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 11:12:29 by agelloz           #+#    #+#              #
#    Updated: 2019/05/10 18:06:06 by agelloz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = fillit
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBH = libft/includes
LIBA = libft/libft.a

SRC = fillit.c get_next_line.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBA) $(OBJ) Makefile
	$(CC) $(CFLAGS) -I$(LIBH) -Llibft -lft -o $(NAME) -g $(OBJ)

$(LIBA):
	make -C libft

%.o: %.c
		$(CC) $(CFLAGS) -I$(LIBH) -o $@ -c $<

clean:
	make -Clibft fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
