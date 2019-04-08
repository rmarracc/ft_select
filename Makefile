#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/11 09:56:48 by rmarracc          #+#    #+#              #
#    Updated: 2019/02/22 00:21:09 by rmarracc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_select
SRC = main.c signal_handler.c signal_func.c terminal.c input.c display.c input_extra.c
OBJ = $(SRC:.c=.o)
CC = gcc
SANITIZE = -fsanitize=address
DEBUG = 0
ifeq ($(DEBUG), 1)
	CFLAGS = -Wall -Wextra -I. -g
else
	CFLAGS = -Wall -Wextra -Werror -I.
endif

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft -ltermcap

clean :
	@make -C libft/ clean
	@rm -f $(OBJ)

fclean : clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
