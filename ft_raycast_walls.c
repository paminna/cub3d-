/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:06:10 by paminna           #+#    #+#             */
/*   Updated: 2021/04/06 17:19:12 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_tex(t_ray *ray, t_data *img, int *c)
{
	ray->side_dist_x += ray->delta_dist_x;
	img->map_x += ray->step_x;
	ray->side = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->tex_h = img->sides[0].height;
		ray->tex_w = img->sides[0].width;
		*c = 0;
	}
	if (ray->ray_dir_x > 0)
	{
		ray->tex_h = img->sides[1].height;
		ray->tex_w = img->sides[1].width;
		*c = 1;
	}
}

void	ft_tex_2(t_ray *ray, t_data *img, int *c)
{
	ray->side_dist_y += ray->delta_dist_y;
	img->map_y += ray->step_y;
	ray->side = 1;
	if (ray->ray_dir_y < 0)
	{
		ray->tex_h = img->sides[2].height;
		ray->tex_w = img->sides[2].width;
		*c = 2;
	}
	if (ray->ray_dir_y > 0)
	{
		ray->tex_h = img->sides[3].height;
		ray->tex_w = img->sides[3].width;
		*c = 3;
	}
}

void	ft_calc_tex(t_ray *ray, t_data *img, int *x)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ((double)img->map_x - ray->pos_x +
		(1 - (double)ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = ((double)img->map_y - ray->pos_y +
		(1 - (double)ray->step_y) / 2) / ray->ray_dir_y;
	img->buf[*x] = ray->perp_wall_dist;
	ray->lineheight = (int)(img->win.height / ray->perp_wall_dist);
	ray->drawstart = -ray->lineheight / 2 + img->win.height / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + img->win.height / 2;
	if (ray->drawstart >= img->win.height)
		ray->drawend = img->win.height - 1;
	if (ray->side == 0)
		ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)ray->tex_w);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = ray->tex_w - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = ray->tex_w - ray->tex_x - 1;
	ray->step = 1.0 * ray->tex_h / ray->lineheight;
}

void	ft_draw(t_data *img, int *y, int *x, int *c)
{
	int j;

	j = 0;
	while (j++ < img->ray.drawstart)
		my_mlx_pixel_put(img, *x, j, img->ray.f);
	while (j < img->ray.drawend && j < img->win.height)
	{
		img->ray.tex_y = (int)(img->ray.tex_pos);
		img->ray.tex_pos += img->ray.step;
		img->ray.color = my_mlx_pixel_get(&img->sides[*c],
		img->ray.tex_x, img->ray.tex_y);
		my_mlx_pixel_put(img, *x, j, img->ray.color);
		j++;
	}
	j = img->ray.drawend;
	while (j++ < img->win.height)
		my_mlx_pixel_put(img, *x, j, img->ray.c);
	*y = j;
}
