# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fginja-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 16:13:37 by fginja-d          #+#    #+#              #
#    Updated: 2018/01/30 16:13:39 by fginja-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl

LIBFT = ./libft

LAGS = -Wall -Wextra -Werror

SRC = get_next_line.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

%.c:%.o
	gcc -c $(FLAGS) $(SRC) -o $(OBJ)

$(NAME) :$(OBJ)
	@make -C $(LIBFT)
	@gcc $(FLAGS) $(SRC) -L libft -lft -o gnl

all : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all