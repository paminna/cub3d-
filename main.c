/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:04 by paminna           #+#    #+#             */
/*   Updated: 2021/03/19 16:18:57 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void					ft_initialize(t_data *img)
{
	img->win.bits_per_pixel = 0;
	img->win.endian = 0;
	img->win.line_length = 0;
	// img->x = 0;
	// img->y = 0;
	img->mapX = 0;
	img->mapY = 0;
	img->ray.cameraX = 0;
	img->ray.hit = 0;
	img->ray.lineheight = 0;
	img->ray.perpWallDist = 0;
	img->ray.side = 0;
	img->sprites.num_sprites = 0;
	img->sprites.sprite_count = 0;
}

void					my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char    *dst;
	if (y < screenHeight && x < screenWidth && x >= 0 && y >= 0)
	{
    	dst = data->win.addr + (y * data->win.line_length + x * (data->win.bits_per_pixel / 8));
    	*(unsigned int*)dst = color;
	}
}

int					my_mlx_pixel_get(t_img *data, int x, int y)
{
	int color;
	color = 0;
	if (!data->width || !data->height)
		return (0);
	x = abs(x);
	y = abs(y);
	if ((x > data->width || y > data->height || x < 0 || y < 0))
		return (0);
	color = *(int *)(data->addr + ((x + (y * data->width))
		* (data->bits_per_pixel / 8)));
	return (color);
}

void ft_check_w_s(t_data *img, int keycode)
{
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
}

void ft_check_d_a(t_data *img, int keycode)
{
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
}

void ft_check_arrows(t_data *img, int keycode)
{
	double oldDirX;
	double oldPlaneX;

	oldPlaneX = img->ray.planeX;
	oldDirX = img->ray.dirX;
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
}

int	win_close(int keycode, t_data *img)
{
	ft_check_w_s(img, keycode);
	ft_check_d_a(img, keycode);
	ft_check_arrows(img, keycode);
	mlx_destroy_image(img->mlx, img->win.img);
	img->win.img = mlx_new_image(img->mlx, 800, 580);
	img->win.addr = mlx_get_data_addr(img->win.img, &img->win.bits_per_pixel, &img->win.line_length,
                                 &img->win.endian);
	ft_raycast(img, &img->ray);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->win.img, 0, 0);
	if (keycode == ESC)
		exit(0);
	return (0);
}

void ft_init_img(t_data *img)
{
	if (!(img->sides[0].img = mlx_xpm_file_to_image(img->mlx, img->sides[0].side , &img->sides[0].width, &img->sides[0].height)))
		ft_errors("Wrong textures");
	img->sides[0].addr = mlx_get_data_addr(img->sides[0].img, &img->sides[0].bits_per_pixel, &img->sides[0].line_length,
                                &img->sides[0].endian);
	if (!(img->sides[1].img = mlx_xpm_file_to_image(img->mlx, img->sides[1].side , &img->sides[1].width, &img->sides[1].height)))
		ft_errors("Wrong textures");
	img->sides[1].addr = mlx_get_data_addr(img->sides[1].img, &img->sides[1].bits_per_pixel, &img->sides[1].line_length,
                                &img->sides[1].endian);
	if (!(img->sides[2].img = mlx_xpm_file_to_image(img->mlx, img->sides[2].side , &img->sides[2].width, &img->sides[2].height)))
		ft_errors("Wrong textures");
	img->sides[2].addr = mlx_get_data_addr(img->sides[2].img, &img->sides[2].bits_per_pixel, &img->sides[2].line_length,
                                &img->sides[2].endian);
	if (!(img->sides[3].img = mlx_xpm_file_to_image(img->mlx, img->sides[3].side , &img->sides[3].width, &img->sides[3].height)))
		ft_errors("Wrong textures");
	img->sides[3].addr = mlx_get_data_addr(img->sides[3].img, &img->sides[3].bits_per_pixel, &img->sides[3].line_length,
                                &img->sides[3].endian);
	if (!(img->sides[4].img = mlx_xpm_file_to_image(img->mlx, img->sides[4].side , &img->sides[4].width, &img->sides[4].height)))
		ft_errors("Wrong textures");
	img->sides[4].addr = mlx_get_data_addr(img->sides[4].img, &img->sides[4].bits_per_pixel, &img->sides[4].line_length,
                                &img->sides[4].endian);
}


int main(void)
{
	t_data img;

	ft_initialize(&img);
	ft_parser(&img.ray, &img);
	img.mlx = mlx_init();
	ft_init_img(&img);
	img.mlx_win = mlx_new_window(img.mlx, img.win.width, img.win.height, "Cutie pie");
	img.win.img = mlx_new_image(img.mlx, img.win.width, img.win.height);
	img.win.addr = mlx_get_data_addr(img.win.img, &img.win.bits_per_pixel, &img.win.line_length,
                                 &img.win.endian);
	ft_raycast(&img, &img.ray);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.win.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 1L<<0, &win_close, &img);
	mlx_loop(img.mlx);
}