/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:08:33 by paminna           #+#    #+#             */
/*   Updated: 2021/02/16 20:31:24 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_init(t_ray *ray)
{
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	// img->mapX = (double)img->x;
	// img->mapY = (double)img->y;
	ray->hit = 0;
}

void ft_raycast(t_data *img, t_ray *ray)
{
	int i;

	i = 1;
	ft_init(ray);
	while (i++ != screenWidth)
	{
		ray->cameraX = 2 * i / (double)screenWidth - 1;
		ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
		ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
		if (ray->rayDirY == 0)
			ray->deltaDistX = 0;
		else
		{
			if (ray->rayDirX == 0)	
				ray->deltaDistX = 1;
			else 
				ray->deltaDistX = fabs(1 / ray->rayDirX);
		}
		if (ray->rayDirX == 0)
			ray->deltaDistY = 0;
		else
		{

			if (ray->rayDirY == 0)	
				ray->deltaDistY = 1;
			else 
				ray->deltaDistY = fabs(1 / ray->rayDirY);
		}
		if (ray->rayDirX < 0)
		{
			ray->stepX = -1;
			ray->sideDistX = (ray->player.posX - img->mapX) * ray->deltaDistX;
		}
		else
		{
			ray->stepX = 1;
			ray->sideDistX = (img->mapX + 1.0 - ray->player.posX) * ray->deltaDistX;
		}
		if (ray->rayDirY < 0)
		{
			ray->stepY = -1;
			ray->sideDistY = (ray->player.posY - img->mapY) * ray->deltaDistY;
		}
		else
		{
			ray->stepY = 1;
			ray->sideDistY = (img->mapY + 1.0 - ray->player.posY) * ray->deltaDistY;
		}
		while (ray->hit == 0)
		{
			if (ray->sideDistX < ray->sideDistY)
			{
				ray->sideDistX += ray->deltaDistX;
				img->mapX += ray->stepX;
				ray->side = 0;
			}
			else
			{
				ray->sideDistY += ray->deltaDistY;
				img->mapY += ray->stepY;
				ray->side = 1;
			}
			if (img->map[img->mapX][img->mapY] != 0)
				ray->hit = 1;
		}
	}
}