# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agelloz <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 11:12:29 by agelloz           #+#    #+#              #
#    Updated: 2019/05/08 17:07:09 by agelloz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iincludes -c
SRC = ft_isprint.c ft_lstnew.c ft_memmove.c ft_putnbr_fd.c ft_strcpy.c \
ft_strjoin.c ft_strncmp.c ft_strstr.c ft_atoi.c ft_itoa.c ft_memalloc.c \
ft_memset.c ft_putstr.c ft_strdel.c ft_strjoinfree.c ft_strncpy.c ft_strsub.c \
ft_bzero.c ft_lstadd.c ft_memccpy.c ft_putchar.c ft_putstr_fd.c ft_strdup.c \
ft_strlcat.c ft_strnequ.c ft_strtrim.c ft_isalnum.c ft_lstdel.c ft_memchr.c \
ft_putchar_fd.c ft_strcat.c ft_strdupfree.c ft_strlen.c ft_strnew.c \
ft_tolower.c ft_isalpha.c ft_lstdelone.c ft_memcmp.c ft_putendl.c ft_strchr.c \
ft_strequ.c ft_strmap.c ft_strnstr.c ft_toupper.c ft_isascii.c ft_lstiter.c \
ft_memcpy.c ft_putendl_fd.c ft_strclr.c ft_striter.c ft_strmapi.c \
ft_strrchr.c ft_isdigit.c ft_lstmap.c ft_memdel.c ft_putnbr.c ft_strcmp.c \
ft_striteri.c ft_strncat.c ft_strsplit.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): Makefile
	@$(CC) $(CFLAGS) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "static library created: libft.a"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
