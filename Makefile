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
CFLAGS = -Wall -Wextra -Werror
CC = gcc
DIR_LIB = ./src/libft/
DIR_SRC	= ./src/
FUNCTIONS =		main.c				\
				fdf_init.c			\
				image.c				\
				painting.c			\
				proy_iso.c			\
				proy_conic.c		\
				animate.c			\
				reload.c			\
				map_color.c			\
				map_outils.c		\
				map_error.c			\
				map.c				\
				be_free.c			\
				triangulate.c

DIR_UI = ./UI/
F_UI =			ui_hooks.c			\
				ui_hooks_outils.c	\
				ui_hooks_outils2.c	\
				ui_menu.c			\
				ui_vars_update.c	\
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


${NAME}:	${OBJS} libft
			$(CC) $(CFLAGS) ${OBJS} $(DIR_LIB)libft.a -lmlx -framework OpenGL -framework AppKit -o $(NAME)

#all: $(NAME)
all: libft	$(NAME)

clean:
			rm -f $(OBJS)
			make clean -C $(DIR_LIB)

fclean: clean
			rm -f $(NAME)
			make fclean -C $(DIR_LIB)

re: fclean all

libft:	$(DIR_LIB)
			make -C $(DIR_LIB)

pyramide:	$(NAME)
			./fdf test_maps/pyramide.fdf

small:		$(NAME)
			./fdf test_maps/test.fdf

pylone:		$(NAME)
			./fdf test_maps/pylone.fdf

world:		$(NAME)
			./fdf test_maps/World.fdf
