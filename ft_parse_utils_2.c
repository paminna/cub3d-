/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:21:11 by paminna           #+#    #+#             */
/*   Updated: 2021/04/01 15:50:37 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_find_pl(t_ray *ray, t_data *img, char *line, int *i)
{
	ray->posX = img->mapX + 0.5;
	ray->posY = *i + 0.5;
	ray->planeX = 0;
	ray->dirY = 0;
	if (line[*i] == 'N')
	{
		ray->planeY = 0.66;
		ray->dirX = -1;
	}
	if (line[*i] == 'S')
	{
		ray->planeY = -0.66;
		ray->dirX = 1;
	}
	img->map[img->mapX][*i] = '0';
	img->flags.pl++;
}

void	ft_find_pl_2(t_ray *ray, t_data *img, char *line, int *i)
{
	ray->posX = img->mapX + 0.5;
	ray->posY = *i + 0.5;
	ray->planeY = 0;
	ray->dirX = 0;
	if (line[*i] == 'W')
	{
		ray->planeX = -1;
		ray->dirY = -0.66;
	}
	if (line[*i] == 'E')
	{
		ray->planeX = 1;
		ray->dirY = 0.66;
	}
	img->map[img->mapX][*i] = '0';
	img->flags.pl++;
}

void	ft_count_sprite(t_data *img, char *line, int *i)
{
	int j;

	j = *i;
	while ((line[j] == '1' || line[j] == '2' || line[j] == '0' || line[j] == ' '
	|| line[j] == 32 || (line[j] > 8 && line[j] < 14)) && (line[j] != '\0'))
	{
		while (line[j] == '1' || line[j] == '0' || line[j] == 'N'
		|| line[j] == 'W' || line[j] == 'E' || line[j] == 'S'
		|| line[j] == ' ' || (line[j] > 8 && line[j] < 14))
			j++;
		while (line[j++] == '2')
			img->spr.num_sprites++;
	}
	j = 0;
	free(line);
	*i = j;
}

void	ft_count_lines(t_data *img)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("map.cub", O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		if ((int)ft_strlen(line) > img->max_len)
			img->max_len = (int)ft_strlen(line);
		if ((line[i] == '1' || line[i] == '2' || line[i] == '0'
		|| line[i] == ' ' || line[i] == 32 ||
		(line[i] > 8 && line[i] < 14)) && (line[i] != '\0'))
			img->size++;
		ft_count_sprite(img, line, &i);
	}
	free(line);
	img->size++;
	close(fd);
	if (!(img->map = (char**)malloc((img->size + 1) * sizeof(char*))))
		ft_errors("Malloc error");
	if (!(img->one = (t_ones*)malloc(sizeof(t_ones)
	* (img->spr.num_sprites))))
		ft_errors("Malloc error");
}

void	ft_check_map(t_data *img)
{
	img->mapX = 0;
	while (img->mapX < img->size)
	{
		img->mapY = 0;
		while (img->mapY < img->max_len)
		{
			if (img->map[img->mapX][img->mapY] != '1'
			&& img->map[img->mapX][img->mapY] != '2'
			&& img->map[img->mapX][img->mapY] != '0'
			&& img->map[img->mapX][img->mapY] != ' '
			&& img->map[img->mapX][img->mapY] != '\t'
			&& img->map[img->mapX][img->mapY] != 'N'
			&& img->map[img->mapX][img->mapY] != 'E'
			&& img->map[img->mapX][img->mapY] != 'W'
			&& img->map[img->mapX][img->mapY] != 'S')
				ft_errors("wrong map");
			img->mapY++;
		}
		img->mapX++;
	}
	if (img->flags.r == 0 || img->flags.t != 5 || img->flags.c == 0)
		ft_errors("not enought data");
}
