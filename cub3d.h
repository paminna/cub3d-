/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:57 by paminna           #+#    #+#             */
/*   Updated: 2021/03/15 18:24:44 by paminna          ###   ########.fr       */
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
#  define pink 0xFFC0CB
#  define orange 0xFF5733
#  define movespeed 0.1
#  define rotation 0.2
#  define blue 0xB0E0E6
#  define green 0x90EE90
# endif

#include "libft/libft.h"
# include "minilibx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h> //

// typedef struct			s_player
// {
// 	double	posX;
// 	double	posY;
// }						t_player;

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
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	posX;
	double	posY;
	int 	color;
	int		c;
	int		f;
	double	tex_pos;
	int		tex_h;
	int		tex_w;
	double	wall_h;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	void	*tex;
	double	pos_s_x;
	double	pos_s_y;
}						t_ray;

typedef	struct 			s_ones
{
 	double				x;
  	double				y;
  	int					texture;
	double				*spriteDistance;
}						t_ones;

typedef	struct 			s_sprites
{
	void        		*img;
    char       			*addr;
    int         		bits_per_pixel;
    int         		line_length;
    int         		endian;
	int					*sprite_order;
	int					num_sprites;
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					sprite_screen_x;
	int					sprite_height;
	int					sprite_width;
	int					draw_start_y;
	int					draw_end_y;
	int					draw_start_x;
	int					draw_end_x;
	int					stripe;
	int					tex_x;
	int					tex_y;
}						t_sprites;

typedef struct			s_img
{
	void        		*img;
    char       			*addr;
    int         		bits_per_pixel;
    int         		line_length;
    int         		endian;
	int					width;
	int					height;
	char				*side;
}						t_img;

typedef struct  		s_data
{
	unsigned int 		color;
	void 				*mlx;
	void 				*mlx_win;
	// int					x;
	// int					y;
	int 				mapX;
	int 				mapY;
	char	 			**map;
	double				*buf;
	t_img				tex;
	t_img				sides[4];
	t_img				win;		
	t_ray				ray;
	t_sprites			sprites;
	t_ones				*one;
}               		t_data;

int		n_in_rem(char *str_n, char **remainder, char **line);
int		r_less_null(char **remainder);
int		r_null(char **line, char **remainder);
int		get_next_line(int fd, char **line);
t_data	*make_map(t_list **head, int size, t_data *img);
void 	find_player(t_data *img, t_ray *player);
void 	redraw(t_data *img);
void	ft_initialize(t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);
void 	draw_square(t_data *img, int i, int j);
void 	draw_map(t_data *img);
int		win_close(int keycode, t_data *img);
void	ft_raycast(t_data *img, t_ray *ray);
void 	ft_init(t_ray *ray);
void 	ft_parser(t_ray *ray, t_data *img);
void	ft_parse_map(char *line, t_ray *ray, t_data *img);
void 	ft_parse_color(char *line, int *side);
void 	ft_parse_tex(char *line, char **side);
void 	ft_parse_resolution(t_data *imgg, char *line);
void 	ft_errors(char *ans);
void 	ft_init_tex(t_data *img);
int	my_mlx_pixel_get(t_img *data, int x, int y);
// void 	ft_cast_ray(t_data *img);
// void 	ft_init_ray(t_ray *ray, t_data *img);

#endif