# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/04 15:47:14 by paminna           #+#    #+#              #
#    Updated: 2021/04/07 09:39:29 by paminna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_parser.c get_next_line.c ft_raycast.c ft_screenshoot.c ft_validate.c\
ft_sprites.c ft_parse_utils.c ft_parse_utils_2.c ft_utils.c ft_moving.c ft_raycast_walls.c

OBJS		=	${SRCS:.c=.o}

NAME		=	cub3d

HEADER	= 	cub3d.h

MAKELIB		=	$(MAKE) -C ./libft

MAKELIBBONUS	=	$(MAKE) bonus -C ./libft

MAKEMLX			= $(MAKE) -C ./minilibx

RM			=	rm -f

CC			=	gcc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g -Imlx -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
		$(MAKELIB)
		$(MAKELIBBONUS)
		$(MAKEMLX)
		mv -f ./libft/libft.a ./
		mv -f ./minilibx/libmlx.a ./
		$(CC) $(OBJS) -lmlx -L. -lft -framework OpenGL -framework AppKit -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}
			$(MAKE) clean -C ./libft

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re