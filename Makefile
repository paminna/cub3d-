# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/04 15:47:14 by paminna           #+#    #+#              #
#    Updated: 2021/02/05 17:08:45 by paminna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = main.c 

OBJS = ${SRCS:.c=.o}

NAME = cub3d

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

LIBFLAG = -L. -lmlx -framework OpenGL -framework AppKit 
.c.o:
			 	${CC} ${CFLAGS} -c $< 

$(NAME):		${OBJS}
				$(MAKE) -C minilibx  && mv minilibx/libmlx.a . && rm -rf minilibx/libmlx.a
				$(CC) $(CFLAGS) $(OBJS) $(LIBFLAG) -o $(NAME)

all: ${NAME}

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY: all clean fclean re