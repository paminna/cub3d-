/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:41:45 by paminna           #+#    #+#             */
/*   Updated: 2021/03/26 18:31:19 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int ft_validator(char **map, int x, int y, int num_lines)
{
	char * res;

	res = ft_strchr("10234NEWS", map[x][y]);
	if (x < 0 || y < 0 || x > num_lines || !map[x][y] || !res)
		return (0);
	if (map[x][y] == '1' || map[x][y] == '3' || map[x][y] == '4')
		return (1);
	if (map[x][y] == '0')
		map[x][y] = '3';
	if (map[x][y] == '2')
		map[x][y] = '4';
	return (ft_validator(map, x, y - 1, num_lines) &&
			ft_validator(map, x, y + 1, num_lines) &&
			ft_validator(map, x - 1, y, num_lines) &&
			ft_validator(map, x + 1, y, num_lines));
}

void ft_validate(t_data *img)
{
	int len;
	int res;
	
	res = 0;
	img->mapX = 0;
	while (img->mapX < img->size)
	{
		len = ft_strlen(img->map[img->mapX]);
		img->mapY = 0;
		while (img->mapY < len)
		{
			if (ft_strchr("10234NEWS", img->map[img->mapX][img->mapY]))
				res = ft_validator(img->map, img->mapX, img->mapY, img->size);
			if (!res)
				break ;
			img->mapY++;
		}
		img->mapX++;
	}
}
