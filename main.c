/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:04 by paminna           #+#    #+#             */
/*   Updated: 2021/02/05 20:45:21 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void					ft_initialize(t_data *img)
{
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
	img->x = 15;
	img->y = 15;
	img->color = 0xFFC0CB;
	// player->color =0xFF5733; 
	img->i = 0;
	img->j = 0;
	img->map[5][5] =
	{
		{'1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '1'},
		{'1', '0', 'p', '0', '1'},
		{'1', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1'}
	;
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
}

void draw_map(t_data *img)
{
	// int i;
	// int j;

	// i = 0;
	// j = 0;
	// char map[5][5] =
	// {	
	// 	{'1', '1', '1', '1', '1'},
	// 	{'1', '0', '0', '0', '1'},
	// 	{'1', '0', 'p', '0', '1'},
	// 	{'1', '0', '0', '0', '1'},
	// 	{'1', '1', '1', '1', '1'}
	// };
	while (i < 5)
	{
		while (j < 5)
		{
			if (map[i][j] == '1')
				draw_square(img, i + 15, j + 15, 20);
			// if (map[i][j] == 'p')
			// {
			// 	img->x = i;
			// 	img->y = j;
			// 	draw_square(img, i + 13, j + 13, 10);
			// }
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 15, 15);
}

int	win_close(int keycode, t_data *img)
{
	if (keycode == 2)
	{
		img->x += 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
		draw_map(img);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 15, 15);
	}
	if (keycode == 0)
	{
		img->x -= 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
		draw_map(img);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 15, 15);
	}
	if (keycode == 13)
	{
		img->y -= 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
		draw_map(img);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 15, 15);
	}
	if (keycode == 1)
	{
		img->y += 1;
		mlx_destroy_image(img->mlx, img->img);
		redraw(img);
		draw_map(img);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 15, 15);
	}
	return (0);
}


int main(void)
{
	t_data img;
	// t_player player;
	
	ft_initialize(&img);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 800, 580, "Hey, cutie pie!");
	redraw(&img);
	draw_map(&img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 15, 15);
	mlx_hook(img.mlx_win, 2, 1L<<0, win_close, &img);
	mlx_loop(img.mlx);
}