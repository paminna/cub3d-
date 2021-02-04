/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@stud.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:04 by paminna           #+#    #+#             */
/*   Updated: 2021/02/03 19:47:07 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx_opengl_20191021/mlx.h"

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
}               		t_data;

void					ft_initialize(t_data *img)
{
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
	img->x = 2;
	img->y = 10;
	img->color = 0xFFC0CB;
}

void					my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_square(t_data *img, int i, int j, int scale)
{
	int i2 = i * scale;
	int j2 = j * scale;
	while (i2 < (i + 1) * scale)
	{
		j2 = j * scale;
		while (j2 < (j + 1) * scale)
		{
			my_mlx_pixel_put(img, i2, j2, img->color);
			j2++;
		}
		i2++;
	}
}

void redraw(t_data *img)
{
	img->img = mlx_new_image(img->mlx, 800, 580);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
                                 &img->endian);
 	draw_square(img, img->x, img->y, 20);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

int	win_close(int keycode, t_data *img)
{
	if (keycode == 2)
	{
		img->x += 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
	}
	if (keycode == 0)
	{
		img->x -= 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
	}
	if (keycode == 13)
	{
		img->y -= 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
	}
	if (keycode == 1)
	{
		img->y += 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
	}
	return (0);
}

int main(void)
{
	t_data img;
	char    *dst;

	ft_initialize(&img);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 800, 580, "Hey, cutie pie!");
	// img.img = mlx_new_image(img.mlx, 800, 580);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                              &img.endian);
 	// draw_square(&img, img.x, img.y, 20);
	// mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	redraw(&img);
	mlx_hook(img.mlx_win, 2, 1L<<0, win_close, &img);
	mlx_loop(img.mlx);
}