# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/22 00:33:10 by flevesqu          #+#    #+#              #
#    Updated: 2016/08/19 08:45:20 by flevesqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCLUDES = libft/includes/

SRC = main.c\
	  fdf.c\
	  init.c\
	  line.c\
	  fdf_2.c

WFLAGS = -Wall -Werror -Wextra -O3 -march=native

LFLAGS = -L libft/ -lft -lm -lmlx -framework OpenGL -framework AppKit

CC = gcc

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c $(NAME).h
	$(CC) -c $(WFLAGS) -I $(INCLUDES) $< -o $@

$(NAME) : $(OBJ) $(NAME).h
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(LFLAGS)

clean :
	rm -rf $(OBJ)

lclean :
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)

lfclean :
	make -C libft/ fclean

re : fclean all

lre :
	make -C libft/ re

.PHONY: all clean fclean re lclean lfclean lre
