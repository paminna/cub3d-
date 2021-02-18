# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/04 15:47:14 by paminna           #+#    #+#              #
#    Updated: 2021/02/18 18:32:24 by paminna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_parser.c get_next_line.c ft_raycast.c

OBJS = ${SRCS:.c=.o}

NAME = cub3d

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

LIBFLAG = -L. -lmlx -framework OpenGL -framework AppKit 
.c.o:
			 	${CC} ${CFLAGS} ${LIBFLAGS} -c $< 
init : 
			$(MAKE) -C libft
			$(MAKE) -C minilibx
			
$(NAME):		${OBJS}
				mv minilibx/libmlx.a . && rm -rf minilibx/libmlx.a
				mv libft/libft.a . && rm -rf libft/libft.a
				$(CC) $(CFLAGS) $(OBJS) libft.a $(LIBFLAG) -o $(NAME)

all: init ${NAME}

clean:
				$(MAKE) -C libft clean
				${RM} ${OBJS}

fclean:			clean
				$(MAKE) -C libft clean
				${RM} ${NAME}

re:				fclean all

.PHONY: all clean fclean re