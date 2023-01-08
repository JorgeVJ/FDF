# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 17:31:12 by jvasquez          #+#    #+#              #
#    Updated: 2022/07/21 21:52:50 by jvasquez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mlx_menu.a
CFLAGS = -Wall -Wextra -Werror
FUNCTIONS = ui_menu.c

OBJS = ${FUNCTIONS:.c=.o}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS} 

all: $(NAME)

clean:
			rm -f $(OBJS)

fclean: clean
			rm -f $(NAME)

re: fclean all
