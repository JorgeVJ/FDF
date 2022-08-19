# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 15:43:41 by jvasquez          #+#    #+#              #
#    Updated: 2022/08/19 20:29:29 by jvasquez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -g -Wall -Wextra -Werror
FUNCTIONS =		main.c				\
				hooks.c				\
				color.c				\
				interfaz.c			\
				points.c			\
				image.c				\
				map.c
FUNCTIONS_GNL = get_next_line.c			\
				get_next_line_utils.c	
DIR_GNL = ./gnl/

#GFUNCTIONS = $(addprefix $(DIR_GNL), ${FUNCTIONS_GNL})
OBJS = ${FUNCTIONS:.c=.o}
GOBJS = $(addprefix $(DIR_GNL), ${FUNCTIONS_GNL:.c=.o})

${NAME}:	${OBJS} ${GOBJS}
			gcc $(CFLAGS) ${OBJS} ${GOBJS} libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
			rm -f $(OBJS) $(GOBJS)

fclean: clean
			rm -f $(NAME)

re: fclean all

pepe:	re clean
			make clean
			./fdf test_maps/pyramide.fdf
