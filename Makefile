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

vpath %.h minilibx-linux : minilibx_opengl_20191021

CFLAGS = -Wall -Wextra -Werror  -I$(MLXDIR) -g
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
				normals.c			\
				map.c				\
				be_free.c			\
				triangulate.c

DIR_UI = ./UI/
F_UI =			ui_hooks.c			\
				ui_hooks_outils.c	\
				ui_hooks_outils2.c	\
				menu/ui_menu.c		\
				ui_vars_update.c	\
				ui_colors.c			\
				ui_images.c			\
				ui_help.c			\
				ui_icons.c

DIR_GNL = ./src/gnl/
F_GNL = 		get_next_line.c			\
				get_next_line_utils.c	

# ------------------------ MLX CONFIG ------------------------------

UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
	MLXDIR = minilibx-linux
	MLXFLAGS = -lmlx -lXext -lX11 -lm -lbsd
	MLXLIB = $(MLXDIR)/libmlx_Linux.a $(MLXDIR)/libmlx.a
	KEY_MACRO = -D LINUX
else
	MLXDIR = minilibx_opengl_20191021
	MLXFLAGS = -lm -lmlx -framework OpenGL -framework AppKit
	MLXLIB = $(MLXDIR)/libmlx.a
	KEY_MACRO = -D MACOS
endif

MLXCONFIG = -L$(MLXDIR) $(MLXFLAGS) $(MLXLIB) $(KEY_MACRO)
# -------------------------------------------------------------------

#OBJS = ${FUNCTIONS:.c=.o}
OBJS = $(addprefix $(DIR_SRC), ${FUNCTIONS:.c=.o})
OBJS += $(addprefix $(DIR_GNL), ${F_GNL:.c=.o})
OBJS += $(addprefix $(DIR_UI), ${F_UI:.c=.o})


${NAME}:	${OBJS} $(MLXLIB) libft
			$(CC) $(CFLAGS) ${OBJS} $(DIR_LIB)libft.a $(MLXCONFIG) -o $(NAME) -fsanitize=address -g3

#all: $(NAME)
all: libft	$(NAME)

$(MLXLIB):
		@echo "\n--------------------------\n"
		@echo "Making MLX\n"
		$(MAKE) -C $(MLXDIR)
		@echo "--------------------------\n\n"

clean:
			rm -f $(OBJS)
			make clean -C $(DIR_LIB)
			@echo "Cleaning MLX"
			make clean -C $(MLXDIR)

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
