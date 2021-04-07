/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:57 by paminna           #+#    #+#             */
/*   Updated: 2021/04/07 09:52:06 by paminna          ###   ########.fr       */
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
#  define MOVESPEED 0.1
#  define ROTATION 0.2
# endif

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef struct			s_ray
{
	double				plane_x;
	double				plane_y;
	double				dir_x;
	double				dir_y;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	double				side_dist_x;
	double				side_dist_y;
	int					lineheight;
	int					drawstart;
	int					drawend;
	double				pos_x;
	double				pos_y;
	int					color;
	int					c;
	int					f;
	double				tex_pos;
	int					tex_h;
	int					tex_w;
	double				wall_h;
	double				wall_x;
	int					tex_x;
	int					tex_y;
	double				step;
	void				*tex;
	double				pos_s_x;
	double				pos_s_y;
}						t_ray;

typedef	struct			s_ones
{
	double				x;
	double				y;
	int					texture;
	double				sprite_distance;
}						t_ones;

typedef	struct			s_sprites
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					*sprite_order;
	int					num_sprites;
	double				spr_x;
	double				spr_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					spr_screen_x;
	int					sprite_height;
	int					sprite_width;
	int					draw_start_y;
	int					draw_end_y;
	int					draw_start_x;
	int					draw_end_x;
	int					stripe;
	int					tex_x;
	int					tex_y;
	int					sprite_count;
}						t_sprites;

typedef struct			s_flag
{
	int					r;
	int					save;
	int					pl;
	int					color;
	int					coma;
	int					count_c;
	int					t;
	int					s;
	int					c;
	int					forward;
	int					left;
	int					back;
	int					right;
	int					rleft;
	int					rright;
	int					map_start;
}						t_flag;

typedef struct			s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
	char				*side;
}						t_img;

typedef struct			s_data
{
	unsigned int		color;
	void				*mlx;
	void				*mlx_win;
	int					max_len;
	int					map_x;
	int					map_y;
	char				**map;
	double				*buf;
	int					size;
	t_img				tex;
	t_img				sides[5];
	t_img				win;
	t_ray				ray;
	t_sprites			spr;
	t_ones				*one;
	t_flag				flags;
}						t_data;

void					ft_check_w_s(t_data *img);
void					ft_check_d_a(t_data *img);
void					ft_check_arrows(t_data *img);
int						key_up(int keycode, t_data *img);
int						key_down(int keycode, t_data *img);
void					ft_find_pl(t_ray *ray, t_data *img, char *line, int *i);
void					ft_find_pl_2(t_ray *ray, t_data *img,
							char *line, int *i);
void					ft_count_sprite(t_data *img, char *line, int *i);
void					ft_count_lines(t_data *img);
void					ft_check_map(t_data *img);
void					ft_check_resolution(char *line, t_data *img,
								unsigned int *w, unsigned int *h);
void					ft_check_r(char *line, int *i, int *r, t_data *img);
void					ft_check_g(char *line, int *i,
							int *g, t_data *img);
void					ft_check_b_and_other(char *line, int *i,
							int *b, t_data *img);
void					ft_full_matrix(t_data *img, char *line);
void					ft_parse_resolution(t_data *img, char *line);
void					ft_parse_tex(char *line, char **side, t_data *img);
void					ft_parse_color(char *line, int *side, t_data *img);
void					ft_parse_map(char *line, t_ray *ray, t_data *img);
void					ft_parser(t_ray *ray, t_data *img, char *file);
void					ft_tex(t_ray *ray, t_data *img, int *c);
void					ft_tex_2(t_ray *ray, t_data *img, int *c);
void					ft_calc_tex(t_ray *ray, t_data *img, int *x);
void					ft_draw(t_data *img, int *y, int *x, int *c);
void					ft_sort_sprites(t_data *img, t_ones *one);
void					ft_check_side(t_ray *ray, t_data *img, int *x);
void					ft_check_side_2(t_ray *ray, t_data *img);
void					ft_raycast_help(t_data *img, int *c, t_ray *ray);
void					ft_raycast(t_data *img, t_ray *ray);
int						ft_close(void);
void					ft_errors(char *ans);
void					ft_header(t_img *win, int fd);
void					make_screenshoot(t_data *img);
void					ft_calc_sprite(t_data *img, t_ray *ray, int *i);
void					ft_draw_s(t_data *img, t_ray *ray);
void					ft_sprite_help(t_data *img, t_ray *ray);
void					ft_draw_spr(t_data *img, t_ray *ray);
void					ft_check_string(char *str);
void					ft_condition_of_parse(char *line,
							t_data *img, t_ray *ray);
void					ft_init_img(t_data *img);
void					ft_check_file(const char *str);
void					ft_initialize(t_data *img);
int						ft_validator(char **map, int x, int y, int num_lines);
void					ft_validate(t_data *img);
int						n_in_rem(char *str_n, char **remainder, char **line);
int						r_less_null(char **remainder);
int						r_null(char **line, char **remainder);
int						get_next_line(int fd, char **line);
void					my_mlx_pixel_put(t_data *data, int x,
							int y, unsigned int color);
int						my_mlx_pixel_get(t_img *data, int x, int y);
int						win_close(t_data *img);
void					play(t_data *img, char *str);

#endif
