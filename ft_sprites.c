/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:46:01 by paminna           #+#    #+#             */
/*   Updated: 2021/03/26 22:06:38 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_draw_spr(t_data *img, t_ray *ray)
{
	int i;
	int d;
	int y;
	
	i = 0;
	img->sprites.sprite_order = (int*)malloc(sizeof(int*) * img->sprites.num_sprites);
	while(i < img->sprites.num_sprites)
    {
    	img->sprites.sprite_order[i] = i;
    	img->one[i].spriteDistance = ((ray->posX - img->one[i].x) * (ray->posX - img->one[i].x) + (ray->posY - img->one[i].y) * (ray->posY - img->one[i].y));
		i++;
    }
	ft_sort_sprites(img, img->one);
	i = 0;
	while (i < img->sprites.num_sprites)
	{
		img->sprites.sprite_x = img->one[i].x - ray->posX;
		img->sprites.sprite_y = img->one[i].y - ray->posY;
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
	img->sprites.stripe = img->sprites.draw_start_x;
	while (img->sprites.stripe < img->sprites.draw_end_x)
    {
        img->sprites.tex_x = (int)(256 *
			(img->sprites.stripe - (-img->sprites.sprite_width / 2 + img->sprites.sprite_screen_x)) * img->sides[4].width / img->sprites.sprite_width) / 256;
        if(img->sprites.transform_y  > 0 && img->sprites.stripe >= 0 && img->sprites.stripe < img->win.width && img->sprites.transform_y  < img->buf[img->sprites.stripe])
        y = img->sprites.draw_start_y;
		while (y < img->sprites.draw_end_y)
        {
        	d = (y) * 256 - img->win.height * 128 + img->sprites.sprite_height * 128;
        	img->sprites.tex_y = ((d * img->sides[4].height) / img->sprites.sprite_height) / 256;
			ray->color = my_mlx_pixel_get(&img->sides[4], img->sprites.tex_x, img->sprites.tex_y);
        	if((ray->color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(img, img->sprites.stripe, y, ray->color);
			y++;
		}
		img->sprites.stripe++;
    }
}
}	