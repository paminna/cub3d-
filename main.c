/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:04 by paminna           #+#    #+#             */
/*   Updated: 2021/03/13 19:09:51 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void					ft_initialize(t_data *img)
{
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
	img->x = 0;
	img->y = 0;
	img->color = 0xFFC0CB;
	img->mapX = 0;
	img->mapY = 0;
}

void					my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char    *dst;
	if (y < screenHeight && x < screenWidth && x >= 0 && y >= 0)
	{
    	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    	*(unsigned int*)dst = color;
	}
}

void draw_square(t_data *img, int i, int j)
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

int	win_close(int keycode, t_data *img)
{
	double oldDirX;
	double oldPlaneX;

	oldPlaneX = img->ray.planeX;
	oldDirX = img->ray.dirX;
	if (keycode == W)
	{
		if (img->map[(int)(img->ray.posX)][(int)(img->ray.posY + img->ray.dirY * movespeed)] != '1') 
			img->ray.posY += img->ray.dirY * movespeed;
		if (img->map[(int)(img->ray.posX + img->ray.dirX * movespeed)][(int)(img->ray.posY)] != '1') 
			img->ray.posX += img->ray.dirX * movespeed;
	}
	if (keycode == S)
	{
		if (img->map[(int)(img->ray.posX)][(int)(img->ray.posY - img->ray.dirY * movespeed)] != '1') 
			img->ray.posY -= img->ray.dirY * movespeed;
		if (img->map[(int)(img->ray.posX - img->ray.dirX * movespeed)][(int)(img->ray.posY)] != '1') 
			img->ray.posX -= img->ray.dirX * movespeed;
	}
	if (keycode == D)
	{
		if (img->map[(int)(img->ray.posX)][(int)(img->ray.posY + img->ray.planeY * movespeed)] != '1') 
			img->ray.posY += img->ray.planeY * movespeed;
		if (img->map[(int)(img->ray.posX + img->ray.planeX * movespeed)][(int)(img->ray.posY)] != '1') 
			img->ray.posX += img->ray.planeX * movespeed;
	}
	if (keycode == A)
	{
		if (img->map[(int)(img->ray.posX)][(int)(img->ray.posY - img->ray.planeY * movespeed)] != '1') 
			img->ray.posY -= img->ray.planeY * movespeed;
		if (img->map[(int)(img->ray.posX - img->ray.planeX * movespeed)][(int)(img->ray.posY)] != '1') 
			img->ray.posX -= img->ray.planeX * movespeed;
	}
	if (keycode == 124)
	{	
      img->ray.dirX = img->ray.dirX * cos(-rotation) - img->ray.dirY * sin(-rotation);
      img->ray.dirY = oldDirX * sin(-rotation) + img->ray.dirY * cos(-rotation);
     
      img->ray.planeX = img->ray.planeX * cos(-rotation) - img->ray.planeY * sin(-rotation);
      img->ray.planeY = oldPlaneX * sin(-rotation) + img->ray.planeY * cos(-rotation);
	}
	if (keycode == 123)
	{
		img->ray.dirX = img->ray.dirX * cos(rotation) - img->ray.dirY * sin(rotation);
		img->ray.dirY = oldDirX * sin(rotation) + img->ray.dirY * cos(rotation);
		img->ray.planeX = img->ray.planeX * cos(rotation) - img->ray.planeY * sin(rotation);
		img->ray.planeY = oldPlaneX * sin(rotation) + img->ray.planeY * cos(rotation);
	}
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, 800, 580);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
                                 &img->endian);
	ft_raycast(img, &img->ray);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	if (keycode == ESC)
		exit(0);
	return (0);
}


int main(void)
{
	t_data img;

	ft_initialize(&img);
	ft_parser(&img.ray, &img);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 800, 580, "Hey, cutie pie!");
	img.img = mlx_new_image(img.mlx, 800, 580);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	ft_init(&img.ray);
	ft_raycast(&img, &img.ray);
	printf("player_x = %f\n", img.ray.posX);
	printf("player_x = %f\n", img.ray.posY);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 1L<<0, &win_close, &img);
	mlx_loop(img.mlx);
}