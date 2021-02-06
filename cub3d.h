/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:57 by paminna           #+#    #+#             */
/*   Updated: 2021/02/06 19:59:38 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

#include "libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h> //

typedef struct  		s_data
{
    void        		*img;
    char       			*addr;
    int         		bits_per_pixel;
    int         		line_length;
    int         		endian;
	unsigned int 		color;
	void 				*mlx;
	void 				*mlx_win;
	int					x;
	int					y;
	int 				i;
	int 				j;
	char	 			**map;
}               		t_data;

int		n_in_rem(char *str_n, char **remainder, char **line);
int		r_less_null(char **remainder);
int		r_null(char **line, char **remainder);
int		get_next_line(int fd, char **line);
t_data	*make_map(t_list **head, int size, t_data *img);
void 	find_player(t_data *img);
void 	redraw(t_data *img);
void	ft_initialize(t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);
void 	draw_square(t_data *img, int i, int j, int scale);
void 	draw_map(t_data *img);
int		win_close(int keycode, t_data *img);
// typedef struct			s_player
// {
// 	unsigned int color;
// }						t_player;

#endif