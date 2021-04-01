/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:46:01 by paminna           #+#    #+#             */
/*   Updated: 2021/04/01 15:55:28 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_sprite(t_data *img, t_ray *ray, int *i)
{
	img->spr.spr_x = img->one[*i].x - ray->posX;
	img->spr.spr_y = img->one[*i].y - ray->posY;
	img->spr.inv_det = 1.0 /
			(ray->planeX * ray->dirY - ray->dirX * ray->planeY);
	img->spr.transform_x = img->spr.inv_det *
			(ray->dirY * img->spr.spr_x - ray->dirX * img->spr.spr_y);
	img->spr.transform_y = img->spr.inv_det *
	(-ray->planeY * img->spr.spr_x + ray->planeX * img->spr.spr_y);
	img->spr.spr_screen_x = (int)((img->win.width / 2) *
	(1 + img->spr.transform_x / img->spr.transform_y));
	img->spr.sprite_height = abs((int)
	(img->win.height / img->spr.transform_y));
	img->spr.draw_start_y = -img->spr.sprite_height / 2 + img->win.height / 2;
	if (img->spr.draw_start_y < 0)
		img->spr.draw_start_y = 0;
	img->spr.draw_end_y = img->spr.sprite_height / 2 + img->win.height / 2;
	if (img->spr.draw_end_y >= img->win.height)
		img->spr.draw_end_y = img->win.height - 1;
	img->spr.sprite_width = img->spr.sprite_height;
	img->spr.draw_start_x = -img->spr.sprite_width / 2 + img->spr.spr_screen_x;
	if (img->spr.draw_start_x < 0)
		img->spr.draw_start_x = 0;
	img->spr.draw_end_x = img->spr.sprite_width / 2 + img->spr.spr_screen_x;
	if (img->spr.draw_end_x >= img->win.width)
		img->spr.draw_end_x = img->win.width - 1;
}

void	ft_draw_spr(t_data *img, t_ray *ray)
{
	int i;
	int d;
	int y;
	
	i = 0;
	if (!(img->spr.sprite_order = (int*)malloc(sizeof(int*) * img->spr.num_sprites))) 
		ft_errors("Malloc trouble");
	while(i < img->spr.num_sprites)
    {
    	img->spr.sprite_order[i] = i;
    	img->one[i].spriteDistance = ((ray->posX - img->one[i].x) * (ray->posX - img->one[i].x) +
		(ray->posY - img->one[i].y) * (ray->posY - img->one[i].y));
		i++;
    }
	ft_sort_sprites(img, img->one);
	i = 0;
	while (i < img->spr.num_sprites)
	{
		ft_calc_sprite(img, ray, &i);
		++i;
		img->spr.stripe = img->spr.draw_start_x;
		while (img->spr.stripe < img->spr.draw_end_x)
   		{
        	img->spr.tex_x = (int)(256 *
				(img->spr.stripe - (-img->spr.sprite_width / 2 + img->spr.spr_screen_x)) * img->sides[4].width / img->spr.sprite_width) / 256;
        	if(img->spr.transform_y  > 0 && img->spr.stripe >= 0 && img->spr.stripe < img->win.width && img->spr.transform_y  < img->buf[img->spr.stripe])
        	y = img->spr.draw_start_y;
			while (y < img->spr.draw_end_y - 1)
        	{
        		d = (y) * 256 - img->win.height * 128 + img->spr.sprite_height * 128;
        		img->spr.tex_y = ((d * img->sides[4].height) / img->spr.sprite_height) / 256;
				ray->color = my_mlx_pixel_get(&img->sides[4], img->spr.tex_x, img->spr.tex_y);
        		if((ray->color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(img, img->spr.stripe, y, ray->color);
				y++;
			}
			img->spr.stripe++;
    	}
	}
	free(img->spr.sprite_order);
}
