/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:41:45 by paminna           #+#    #+#             */
/*   Updated: 2021/03/25 19:12:40 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_validator(char **map, int x, int y, int num_sprites)
{
	char c;
	
	c = map[x][y];
	if (x < 0 || y < 0 || x < num_sprites
	|| !(ft_strchr("102NEWS", c)))
		return (0);
	if (c == '1' || c == '3' || c == '4')
		return (1);
	if (c == '0')
		c = '3';
	if (c == '2')
		c = '4';
	return (ft_validator(map, x, y - 1, num_sprites) &&
			ft_validator(map, x, y + 1, num_sprites) &&
			ft_validator(map, x - 1, y, num_sprites) &&
			ft_validator(map, x + 1, y, num_sprites));
}

void ft_validate(t_data *img)
{
	int len;
	int res;
	
	res = 0;
	img->mapX = 0;
	len = ft_strlen(img->map[img->mapX]);
	while (img->mapX <= len)
	{
		img->mapY = 0;
		while (img->mapY < img->sprites.num_sprites)
		{
			if (ft_strchr("102NEWS", img->map[img->mapX][img->mapY]))
				res = ft_validator(img->map, img->mapX, img->mapY, img->sprites.num_sprites);
			if (!res)
				break ;
			img->mapY++;
		}
		img->mapX++;
	}
}