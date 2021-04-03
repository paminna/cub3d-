/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:41:45 by paminna           #+#    #+#             */
/*   Updated: 2021/04/03 18:38:09 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_validator(char **map, int x, int y, int num_lines)
{
	if (x < 0 || y < 0 || x > num_lines ||
		map[x][y] == '\0' || map[x][y] == ' ')
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

void	ft_validate(t_data *img)
{
	int res;

	res = -1;
	img->mapX = 0;
	while (img->mapX < img->size)
	{
		img->mapY = 0;
		while (img->mapY < img->max_len)
		{
			if (img->map[img->mapX][img->mapY] == '0' && res != 0)
				res = ft_validator(img->map, img->mapX, img->mapY, img->size);
			if (res == 0)
				ft_errors("wrong map");
			img->mapY++;
		}
		img->mapX++;
	}
}
