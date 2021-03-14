/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:08:33 by paminna           #+#    #+#             */
/*   Updated: 2021/03/14 20:45:38 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void ft_init(t_ray *ray)
// {
// 	// ray->dirX = -1;
// 	// ray->dirY = 0;
// 	ray->cameraX = 0;
// 	ray->hit = 0;
// 	ray->lineheight = 0;
// 	ray->perpWallDist = 0;
// 	ray->side = 0;
// }

void ft_raycast(t_data *img, t_ray *ray)
{
	int x;
	int y;
	int i;
	int c;
	
	x = -1;
	while (++x < screenWidth)
	{
		ray->cameraX = 2 * x / (double)img->win.width - 1;
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
				if (ray->rayDirX < 0)  // север
				{
					// ray->tex_h = img->sides[0].height;
					// ray->tex_w = img->sides[0].width;
					c = 0;
				}
				if (ray->rayDirX > 0) // юг
				{
					// ray->tex_h = img->sides[1].height;
					// ray->tex_w = img->sides[1].width;
					c = 1;
				}
			}
			else
			{
				ray->sideDistY += ray->deltaDistY;
				img->mapY += ray->stepY;
				ray->side = 1;
				if (ray->rayDirY < 0) // запад
				{
					// ray->tex_h = img->sides[2].height;
					// ray->tex_w = img->sides[2].width;
					c = 2;
				}
				if (ray->rayDirY > 0) // восток
				{
					// ray->tex_h = img->sides[3].height;
					// ray->tex_w = img->sides[3].width;
					c = 3;
					
				}
			}
			if (img->map[img->mapX][img->mapY] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0 )
			ray->perpWallDist = ((double)img->mapX - ray->posX + (1 - (double)ray->stepX) / 2) / ray->rayDirX;
		else
			ray->perpWallDist = ((double)img->mapY - ray->posY + (1 - (double)ray->stepY) / 2) / ray->rayDirY;
		ray->lineheight = (int) (img->win.height / ray->perpWallDist);
		ray->drawstart = -ray->lineheight / 2 + img->win.height / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + img->win.height/ 2;
		if (ray->drawstart >= img->win.height)
			ray->drawend = img->win.height - 1;
      	if (ray->side == 0) 
			ray->wall_x = ray->posY + ray->perpWallDist * ray->rayDirY;
      	else          
			ray->wall_x = ray->posX + ray->perpWallDist * ray->rayDirX;
      	ray->wall_x -= floor((ray->wall_x));
		ray->tex_x = (int)(ray->wall_x * (double)ray->tex_w);
      	if (ray->side == 0 && ray->rayDirX > 0)
			ray->tex_x = ray->tex_w - ray->tex_x - 1;
      	if(ray->side == 1 && ray->rayDirY < 0)
			ray->tex_x = ray->tex_w - ray->tex_x - 1;
		ray->step = 1.0 * ray->tex_h / ray->lineheight;
		ray->tex_pos = (ray->drawstart - img->win.height / 2 + ray->lineheight / 2) * ray->step;
	 	y = 0;
        i = ray->drawend;
        while (y++ < ray->drawstart)
            my_mlx_pixel_put(img, x, y, 28369126);
        y  = ray->drawstart;
        while (y <= ray->drawend)
        {
            // my_mlx_pixel_put(img, x, y, ray->color);
			ray->tex_y = (int)(ray->tex_pos) & (ray->tex_h - 1);
			ray->tex_pos += ray->step;
			ray->color = my_mlx_pixel_get(&img->sides[c], ray->tex_x, ray->tex_y);
			my_mlx_pixel_put(img, x, y, ray->color);
            y++;
        }
        y = i;
        while (y++ < screenHeight)
            my_mlx_pixel_put(img, x, y, green);
	}
}