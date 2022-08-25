# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 15:43:41 by jvasquez          #+#    #+#              #
#    Updated: 2022/08/25 18:43:44 by jvasquez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -Ofast -Wall -Wextra -Werror
CC = gcc
FUNCTIONS =		main.c				\
				hooks.c				\
				color.c				\
				interfaz.c			\
				points.c			\
				image.c				\
				pcono.c				\
				animate.c			\
				map.c
FUNCTIONS_GNL = get_next_line.c			\
				get_next_line_utils.c	
DIR_GNL = ./gnl/

#GFUNCTIONS = $(addprefix $(DIR_GNL), ${FUNCTIONS_GNL})
OBJS = ${FUNCTIONS:.c=.o}
GOBJS = $(addprefix $(DIR_GNL), ${FUNCTIONS_GNL:.c=.o})

${NAME}:	${OBJS} ${GOBJS}
			$(CC) $(CFLAGS) ${OBJS} ${GOBJS} libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
			rm -f $(OBJS) $(GOBJS)

fclean: clean
			rm -f $(NAME)

re: fclean all

pyramide:	re clean
			make clean
			./fdf test_maps/pyramide.fdf
			#./fdf cube
			#./fdf cone
			#./fdf test_maps/julia.fdf
			#./fdf test_maps/elem-fract.fdf
			#./fdf test_maps/elem.fdf
			#./fdf test_maps/pylone.fdf
