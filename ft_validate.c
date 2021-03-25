/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:41:45 by paminna           #+#    #+#             */
/*   Updated: 2021/03/25 14:46:25 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_validator(int x, int y, int num_sprites, char c)
{
	if (x < 0 || y < 0 || x < num_sprites
	|| !(ft_strchr("102NEWS", c)))
		return (1);
	if (c == '1' || c == '3' || c == '4')
		return (0);
	if (c == '0')
		c = '3';
	if (c == '2')
		c = '4';
	return (ft_validator(x, y - 1) && ft_validator(x, y + 1) && ft_validator(x - 1, y) && ft_validator(x + 1, y) )
}

void ft_validate(t_data *img)
{
	int len;
	int res;

	res = 0;
	len = ft_strlen(img->map[img->mapX]);
	img->mapX = 0;
	while (img->mapX <= len)
	{
		img->mapY = 0;
		while (img->mapY < img->sprites.num_sprites)
		{
			if (ft_strchr("102NEWS", img->map[img->mapX][img->mapY]))
				res = ft_validator(img->mapX, img->mapY, img->sprites.num_sprites, img->map[img->mapX][img->mapY]);
			if (!res)
				break ;
			img->mapY++;
		}
		img->mapX++;
	}
}