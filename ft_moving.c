/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moving.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:04:12 by paminna           #+#    #+#             */
/*   Updated: 2021/04/06 17:12:05 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_w_s(t_data *img)
{
	if (img->flags.forward == 1)
	{
		if (img->map[(int)(img->ray.pos_x)]
		[(int)(img->ray.pos_y + img->ray.dir_y * MOVESPEED)] != '1')
			img->ray.pos_y += img->ray.dir_y * MOVESPEED;
		if (img->map[(int)(img->ray.pos_x + img->ray.dir_x * MOVESPEED)]
		[(int)(img->ray.pos_y)] != '1')
			img->ray.pos_x += img->ray.dir_x * MOVESPEED;
	}
	if (img->flags.back == 1)
	{
		if (img->map[(int)(img->ray.pos_x)]
		[(int)(img->ray.pos_y - img->ray.dir_y * MOVESPEED)] != '1')
			img->ray.pos_y -= img->ray.dir_y * MOVESPEED;
		if (img->map[(int)(img->ray.pos_x - img->ray.dir_x * MOVESPEED)]
		[(int)(img->ray.pos_y)] != '1')
			img->ray.pos_x -= img->ray.dir_x * MOVESPEED;
	}
}

void	ft_check_d_a(t_data *img)
{
	if (img->flags.right == 1)
	{
		if (img->map[(int)(img->ray.pos_x)]
		[(int)(img->ray.pos_y + img->ray.plane_y * MOVESPEED)] != '1')
			img->ray.pos_y += img->ray.plane_y * MOVESPEED;
		if (img->map[(int)(img->ray.pos_x + img->ray.plane_x * MOVESPEED)]
		[(int)(img->ray.pos_y)] != '1')
			img->ray.pos_x += img->ray.plane_x * MOVESPEED;
	}
	if (img->flags.left == 1)
	{
		if (img->map[(int)(img->ray.pos_x)]
		[(int)(img->ray.pos_y - img->ray.plane_y * MOVESPEED)] != '1')
			img->ray.pos_y -= img->ray.plane_y * MOVESPEED;
		if (img->map[(int)(img->ray.pos_x - img->ray.plane_x * MOVESPEED)]
		[(int)(img->ray.pos_y)] != '1')
			img->ray.pos_x -= img->ray.plane_x * MOVESPEED;
	}
}

void	ft_check_arrows(t_data *img)
{
	double olddir_x;
	double oldplane_x;
	double rotate;

	oldplane_x = img->ray.plane_x;
	olddir_x = img->ray.dir_x;
	if (img->flags.rright == 1)
		rotate = -ROTATION;
	if (img->flags.rleft == 1)
		rotate = ROTATION;
	if ((img->flags.rright != 1 && img->flags.rleft == 1)
	|| (img->flags.rright == 1 && img->flags.rleft != 1))
	{
		img->ray.dir_x = img->ray.dir_x * cos(rotate) -
		img->ray.dir_y * sin(rotate);
		img->ray.dir_y = olddir_x * sin(rotate) +
		img->ray.dir_y * cos(rotate);
		img->ray.plane_x = img->ray.plane_x * cos(rotate) -
		img->ray.plane_y * sin(rotate);
		img->ray.plane_y = oldplane_x * sin(rotate) +
		img->ray.plane_y * cos(rotate);
	}
}

int		key_up(int keycode, t_data *img)
{
	if (keycode == 13)
		img->flags.forward = 0;
	else if (keycode == 1)
		img->flags.back = 0;
	else if (keycode == 0)
		img->flags.left = 0;
	else if (keycode == 2)
		img->flags.right = 0;
	if (keycode == 123)
		img->flags.rleft = 0;
	if (keycode == 124)
		img->flags.rright = 0;
	if (keycode == ESC)
		exit(0);
	return (0);
}

int		key_down(int keycode, t_data *img)
{
	if (keycode == 13)
		img->flags.forward = 1;
	else if (keycode == 1)
		img->flags.back = 1;
	else if (keycode == 0)
		img->flags.left = 1;
	else if (keycode == 2)
		img->flags.right = 1;
	if (keycode == 123)
		img->flags.rleft = 1;
	if (keycode == 124)
		img->flags.rright = 1;
	if (keycode == ESC)
		exit(0);
	return (0);
}
