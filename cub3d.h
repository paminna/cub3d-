/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:57 by paminna           #+#    #+#             */
/*   Updated: 2021/02/16 20:24:40 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
#  define W 13
#  define S 1
#  define A 0
#  define D 2
#  define ESC 53
#  define screenWidth 800
#  define screenHeight 580
#  define scale 20
#  define step 0.3
# endif

#include "libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
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
	int 				mapX;
	int 				mapY;
	char	 			**map;
}               		t_data;

typedef struct			s_player
{
	double	posX;
	double	posY;
}						t_player;

typedef struct			s_ray
{
	double	planeX;
	double	planeY;
	double	dirX;		//то куда мы смотрим
	double	dirY;		//то куда мы смотрим
	double	cameraX;
	double	rayDirX;	// координаты луча, который мы пускаем, меняется в зависимости от угла луча
	double	rayDirY;	// координаты луча, который мы пускаем, меняется в зависимости от угла луча
	double	deltaDistX;	// расстояние до пересечения со стеной по диагонали
	double	deltaDistY; // расстояние до пересечения со стеной по диагонали
	double	perpWallDist; //расстояние до стены под прямым углом
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	sideDistX;
	double	sideDistY;
	t_player player;
}						t_ray;


int		n_in_rem(char *str_n, char **remainder, char **line);
int		r_less_null(char **remainder);
int		r_null(char **line, char **remainder);
int		get_next_line(int fd, char **line);
t_data	*make_map(t_list **head, int size, t_data *img);
void 	find_player(t_data *img);
void 	redraw(t_data *img);
void	ft_initialize(t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);
void 	draw_square(t_data *img, int i, int j);
void 	draw_map(t_data *img);
int		win_close(int keycode, t_data *img);
void	ft_raycast(t_data *img, t_ray *ray);
// void 	ft_cast_ray(t_data *img);
// void 	ft_init_ray(t_ray *ray, t_data *img);

#endif