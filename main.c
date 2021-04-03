/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:04 by paminna           #+#    #+#             */
/*   Updated: 2021/04/03 19:20:57 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char *dst;

	if (y < data->win.height && x < data->win.width && x >= 0 && y >= 0)
	{
		dst = data->win.addr + (y * data->win.line_length + x *
		(data->win.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

int		my_mlx_pixel_get(t_img *data, int x, int y)
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

int		win_close(t_data *img)
{
	ft_check_w_s(img);
	ft_check_d_a(img);
	ft_check_arrows(img);
	mlx_destroy_image(img->mlx, img->win.img);
	img->win.img = mlx_new_image(img->mlx, img->win.width, img->win.height);
	img->win.addr = mlx_get_data_addr(img->win.img, &img->win.bits_per_pixel,
	&img->win.line_length, &img->win.endian);
	ft_raycast(img, &img->ray);
	if (img->flags.save == 1)
		make_screenshoot(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->win.img, 0, 0);
	return (0);
}

void	play(t_data *img, char *str)
{
	ft_initialize(img);
	ft_check_file(str);
	ft_parser(&img->ray, img, str);
	ft_validate(img);
	img->mlx = mlx_init();
	if (img->flags.save != 1)
		img->mlx_win = mlx_new_window(img->mlx, img->win.width,
		img->win.height, "Cutie pie");
	ft_init_img(img);
	img->win.img = mlx_new_image(img->mlx, img->win.width, img->win.height);
	img->win.addr = mlx_get_data_addr(img->win.img,
	&img->win.bits_per_pixel, &img->win.line_length,
	&img->win.endian);
	win_close(img);
	ft_raycast(img, &img->ray);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->win.img, 0, 0);
	mlx_hook(img->mlx_win, 2, 1L << 0, &key_down, img);
	mlx_hook(img->mlx_win, 17, 1L << 17, ft_close, img);
	mlx_loop_hook(img->mlx, win_close, img);
	mlx_hook(img->mlx_win, 3, 1L << 1, &key_up, img);
	mlx_loop(img->mlx);
}

int		main(int argc, char **argv)
{
	t_data img;

	if (argc < 2 || argc > 3)
		ft_errors("Wrong amount of arguments");
	img.flags.save = 0;
	if (argc == 2)
		play(&img, argv[1]);
	if (argc == 3 && !(ft_strncmp(argv[2], "--save", ft_strlen(argv[2]) + 1)))
	{
		img.flags.save = 1;
		play(&img, argv[1]);
	}
	else
		ft_errors("wrong arguments");
	return (0);
}
