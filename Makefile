# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 15:43:41 by jvasquez          #+#    #+#              #
#    Updated: 2022/08/25 21:28:13 by jvasquez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -Ofast -Wall -Wextra -Werror
CC = gcc
DIR_SRC	= ./src/
FUNCTIONS =		main.c				\
				fdf_init.c			\
				image.c				\
				proy_iso.c			\
				proy_conic.c		\
				animate.c			\
				map_color.c			\
				map_outils.c		\
				map.c				\
				be_free.c			\
				triangulate.c

DIR_UI = ./UI/
F_UI =			ui_hooks.c			\
				ui_hooks_outils.c	\
				ui_hooks_outils2.c	\
				ui_colors.c			\
				ui_images.c			\
				ui_help.c			\
				ui_icons.c

DIR_GNL = ./src/gnl/
F_GNL = 		get_next_line.c			\
				get_next_line_utils.c	

#OBJS = ${FUNCTIONS:.c=.o}
OBJS = $(addprefix $(DIR_SRC), ${FUNCTIONS:.c=.o})
OBJS += $(addprefix $(DIR_GNL), ${F_GNL:.c=.o})
OBJS += $(addprefix $(DIR_UI), ${F_UI:.c=.o})

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) ${OBJS} src/libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
			rm -f $(OBJS)

fclean: clean
			rm -f $(NAME)

re: fclean all

pyramide:	re clean
			make clean
			./fdf test_maps/pyramide.fdf

small:	re clean
			make clean
			./fdf test_maps/10-2.fdf
pylone:	re clean
			make clean
			./fdf test_maps/pylone.fdf
