/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@stud.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:08:33 by paminna           #+#    #+#             */
/*   Updated: 2021/03/08 17:02:20 by paminna          ###   ########.fr       */
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
	ray->hit = 0;
	ray->lineheight = 0;
	ray->perpWallDist = 0;
	ray->side = 0;
}

void ft_raycast(t_data *img, t_ray *ray)
{
	int x;
	int y;
	int i;
	
	x = -1;
	while (++x < screenWidth)
	{
		ray->cameraX = 2 * x / (double)screenWidth - 1;
		ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
		ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
		img->mapX = (int)ray->posX;
		img->mapY = (int)ray->posY;
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
			ray->sideDistX = (ray->posX - img->mapX) * ray->deltaDistX;
		}
		else
		{
			ray->stepX = 1;
			ray->sideDistX = (img->mapX + 1.0 - ray->posX) * ray->deltaDistX;
		}
		if (ray->rayDirY < 0)
		{
			ray->stepY = -1;
			ray->sideDistY = (ray->posY - img->mapY) * ray->deltaDistY;
		}
		else
		{
			ray->stepY = 1;
			ray->sideDistY = (img->mapY + 1.0 - ray->posY) * ray->deltaDistY;
		}
		ray->hit = 0;
		while (ray->hit == 0)
		{
			if (ray->sideDistX < ray->sideDistY)
			{
				ray->sideDistX += ray->deltaDistX;
				img->mapX += ray->stepX;
				ray->side = 0;
				if (ray->rayDirX < 0)
					ray->color = 0xDDA0DD;
				if (ray->rayDirX > 0)
					ray->color = 0xE6E6FA;
			}
			else
			{
				ray->sideDistY += ray->deltaDistY;
				img->mapY += ray->stepY;
				ray->side = 1;
				if (ray->rayDirY < 0)
					ray->color = pink;
				if (ray->rayDirY > 0)
					ray->color = 0xFFE4C4;
			}
			if (img->map[img->mapX][img->mapY] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0 )
			ray->perpWallDist = ((double)img->mapX - ray->posX + (1 - (double)ray->stepX) / 2) / ray->rayDirX;
		else
			ray->perpWallDist = ((double)img->mapY - ray->posY + (1 - (double)ray->stepY) / 2) / ray->rayDirY;
		ray->lineheight = (int) (screenHeight / ray->perpWallDist);
		ray->drawstart = -ray->lineheight / 2 + screenHeight / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + screenHeight / 2;
		if (ray->drawstart >= screenHeight)
			ray->drawend = screenHeight - 1;
		// y = ray->drawstart;
	 	y = 0;
        i = ray->drawend;
        while (y++ < ray->drawstart)
            my_mlx_pixel_put(img, x, y, blue);
        y  = ray->drawstart;
        while (y <= ray->drawend)
        {
            my_mlx_pixel_put(img, x, y, ray->color);
            y++;
        }
        y = i;
        while (y++ < screenHeight)
            my_mlx_pixel_put(img, x, y, green);
		// while (y < ray->drawend)
		// {
		// 	my_mlx_pixel_put(img, x, y, ray->color);
		// 	y++;
		// }
	}
}