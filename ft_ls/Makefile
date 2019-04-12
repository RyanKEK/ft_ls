# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/09 18:10:48 by ohavryle          #+#    #+#              #
#    Updated: 2019/04/11 18:22:26 by ohavryle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = ft_ls

SRC = main.c error.c utils.c

OBJ = main.o error.o utils.o

CFLAGS = -Wall -Wextra -Werror -g

all: lib $(NAME)

lib:
	@$(MAKE) -C libft all
 $(NAME): $(OBJ)
	$(CC) -o $(NAME) -I ft_ls.h -I libft/includes *.o \
	-L libft/  -lft

clean:
	rm -f *.o
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all
