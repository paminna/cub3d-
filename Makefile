# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/04 15:47:14 by paminna           #+#    #+#              #
#    Updated: 2021/04/05 16:02:38 by paminna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_parser.c get_next_line.c ft_raycast.c ft_screenshoot.c ft_validate.c\
ft_sprites.c ft_parse_utils.c ft_parse_utils_2.c ft_utils.c ft_moving.c ft_raycast_walls.c

OBJS = ${SRCS:.c=.o}

NAME = cub3d

HEADER = cub3d.h

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

LIBFLAG = -L. -lmlx -framework OpenGL -framework AppKit 
%.o : %.c
			 	${CC} ${CFLAGS} -Imlx -c $< -o $@
init : 
				$(MAKE) -C libft
				$(MAKE) -C minilibx
			
$(NAME):		${OBJS} $(HEADER)
				init
				mv minilibx/libmlx.a . && rm -rf minilibx/libmlx.a
				mv libft/libft.a . && rm -rf libft/libft.a
				$(CC)$(OBJS) libft.a $(LIBFLAG) -o $(NAME)

all:  ${NAME}

clean:
				$(MAKE) -C libft clean
				${RM} ${OBJS}

fclean:			clean
				$(MAKE) -C libft clean
				${RM} ${NAME}

re:				fclean all

.PHONY: all clean fclean re