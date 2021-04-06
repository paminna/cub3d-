/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:08:33 by paminna           #+#    #+#             */
/*   Updated: 2021/04/06 17:19:12 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sort_sprites(t_data *img, t_ones *one)
{
	int		i;
	int		j;
	t_ones	help;

	i = 0;
	j = 1;
	while (j <= img->spr.num_sprites - 1)
	{
		while (i <= img->spr.num_sprites - 1 - j)
		{
			if (one[i].sprite_distance < one[i + 1].sprite_distance)
			{
				help = one[i];
				one[i] = one[i + 1];
				one[i + 1] = help;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void	ft_check_side(t_ray *ray, t_data *img, int *x)
{
	ray->camera_x = 2 * (*x) / (double)img->win.width - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	img->map_x = (int)ray->pos_x;
	img->map_y = (int)ray->pos_y;
	if (ray->ray_dir_y == 0)
		ray->delta_dist_x = 0;
	else
	{
		if (ray->ray_dir_x == 0)
			ray->delta_dist_x = 1;
		else
			ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	}
	if (ray->ray_dir_x == 0)
		ray->delta_dist_y = 0;
	else
	{
		if (ray->ray_dir_y == 0)
			ray->delta_dist_y = 1;
		else
			ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	}
}

void	ft_check_side_2(t_ray *ray, t_data *img)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - img->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (img->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - img->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (img->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	ft_raycast_help(t_data *img, int *c, t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
		ft_tex(ray, img, c);
	else
		ft_tex_2(ray, img, c);
	if (img->map[img->map_x][img->map_y] == '1')
		ray->hit = 1;
}

void	ft_raycast(t_data *img, t_ray *ray)
{
	int x;
	int y;
	int c;

	if (!(img->buf = (double*)malloc(sizeof(double) * img->win.width)))
		ft_errors("Malloc error");
	x = -1;
	while (++x < img->win.width)
	{
		ft_check_side(ray, img, &x);
		ft_check_side_2(ray, img);
		ray->hit = 0;
		while (ray->hit == 0)
			ft_raycast_help(img, &c, ray);
		ft_calc_tex(ray, img, &x);
		ray->tex_pos = (ray->drawstart - img->win.height / 2
		+ ray->lineheight / 2) * ray->step;
		ft_draw(img, &y, &x, &c);
	}
	ft_draw_spr(img, ray);
	free(img->buf);
}
