/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:08:33 by paminna           #+#    #+#             */
/*   Updated: 2021/03/16 15:49:48 by paminna          ###   ########.fr       */
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
	int d;
		
	if (!(img->buf = (double*)malloc(sizeof(double)*img->win.width)))
		ft_errors("Malloc error");
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
					ray->tex_h = img->sides[0].height;
					ray->tex_w = img->sides[0].width;
					c = 0;
				}
				if (ray->rayDirX > 0) // юг
				{
					ray->tex_h = img->sides[1].height;
					ray->tex_w = img->sides[1].width;
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
					ray->tex_h = img->sides[2].height;
					ray->tex_w = img->sides[2].width;
					c = 2;
				}
				if (ray->rayDirY > 0) // восток
				{
					ray->tex_h = img->sides[3].height;
					ray->tex_w = img->sides[3].width;
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
		img->buf[x] = ray->perpWallDist;
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
			ray->tex_y = (int)(ray->tex_pos); //& (ray->tex_h - 1);
			ray->tex_pos += ray->step;
			ray->color = my_mlx_pixel_get(&img->sides[c], ray->tex_x, ray->tex_y);
			my_mlx_pixel_put(img, x, y, ray->color);
            y++;
        }
        y = i;
        while (y++ < screenHeight)
            my_mlx_pixel_put(img, x, y, green);
	}
	i = 0;
	img->sprites.sprite_order = (int*)malloc(sizeof(int*) * img->sprites.num_sprites);
	img->one->spriteDistance = (double*)malloc(sizeof(t_ones) * img->sprites.num_sprites);
	while (i < img->sprites.num_sprites)
	{
		img->sprites.sprite_order[i] = i;
		img->one->spriteDistance[i] = ((ray->posX - img->one[i].x) * (ray->posX - img->one[i].x) + (ray->posY - img->one[i].y) * (ray->posY - img->one[i].y));
		++i;
	}
	//sort sprites
	i = 0;
	while (i < img->sprites.num_sprites)
	{
		img->sprites.sprite_x = img->one[img->sprites.sprite_order[i]].x - ray->posX;
		img->sprites.sprite_y = img->one[img->sprites.sprite_order[i]].y - ray->posY;
		img->sprites.inv_det = 1.0 / (ray->planeX * ray->dirY - ray->dirX * ray->planeY);
		img->sprites.transform_x = img->sprites.inv_det * (ray->dirY * img->sprites.sprite_x - ray->dirX * img->sprites.sprite_y);
		img->sprites.transform_y = img->sprites.inv_det * (-ray->planeY * img->sprites.sprite_x + ray->planeX * img->sprites.sprite_y);
		img->sprites.sprite_screen_x = (int)((img->win.width / 2) * (1 + img->sprites.transform_x / img->sprites.transform_y));
		img->sprites.sprite_height = abs((int)(img->win.height / img->sprites.transform_y));
		img->sprites.draw_start_y = -img->sprites.sprite_height / 2 + img->win.height / 2;
      	if(img->sprites.draw_start_y < 0) 
			img->sprites.draw_start_y = 0;
      	img->sprites.draw_end_y = img->sprites.sprite_height / 2 + img->win.height / 2;
      	if(img->sprites.draw_end_y >= img->win.height) 
			img->sprites.draw_end_y = img->win.height - 1;
      	img->sprites.sprite_width = abs((int)(img->win.height / (img->sprites.transform_y)));
      	img->sprites.draw_start_x = -img->sprites.sprite_width / 2 + img->sprites.sprite_screen_x;
      	if(img->sprites.draw_start_x < 0)
			img->sprites.draw_start_x = 0;
      	img->sprites.draw_end_x = img->sprites.sprite_width / 2 + img->sprites.sprite_screen_x;
      	if(img->sprites.draw_end_x >= img->win.width)
			img->sprites.draw_end_x = img->win.width - 1;
			++i;
	}
	img->sprites.stripe = img->sprites.draw_start_x;
	while (img->sprites.stripe < img->sprites.draw_end_x)
    {
        img->sprites.tex_x = (int)(
			(img->sprites.stripe - (-img->sprites.sprite_width / 2 + img->sprites.sprite_screen_x)) * img->sides[4].width/ img->sprites.sprite_width) / 256;
        if(img->sprites.transform_y  > 0 && img->sprites.stripe > 0 && img->sprites.stripe < img->win.width && img->sprites.transform_y  < img->buf[img->sprites.stripe])
        y = img->sprites.draw_start_y;
		while (y < img->sprites.draw_end_y)
        {
        	d = (y) * 256 - img->win.height * 128 + img->sprites.sprite_height * 128;
        	img->sprites.tex_y = ((d * img->sides[4].height) / img->sprites.sprite_height) / 256;
			ray->color = my_mlx_pixel_get(&img->sides[4], img->sprites.tex_x, img->sprites.tex_y);
        	// ray->color = texture[sprite[spriteOrder[i]].texture][&img->sides[4].width * img->sprites.tex_y + img->sprites.tex_x]; //get current color from the texture
        	if((ray->color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(img, img->sprites.tex_x, img->sprites.tex_y, ray->color);
				// buffer[y][img->sprites.stripe] = ray->color; //paint pixel if it isn't black, black is the invisible color
			y++;
		}
		img->sprites.stripe++;
    }
}