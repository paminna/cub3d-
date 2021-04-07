/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:21:11 by paminna           #+#    #+#             */
/*   Updated: 2021/04/07 10:35:03 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_find_pl(t_ray *ray, t_data *img, char *line, int *i)
{
	ray->pos_x = img->map_x + 0.5;
	ray->pos_y = *i + 0.5;
	ray->plane_x = 0;
	ray->dir_y = 0;
	if (line[*i] == 'N')
	{
		ray->plane_y = 0.66;
		ray->dir_x = -1;
	}
	if (line[*i] == 'S')
	{
		ray->plane_y = -0.66;
		ray->dir_x = 1;
	}
	img->map[img->map_x][*i] = '0';
	img->flags.pl++;
}

void	ft_find_pl_2(t_ray *ray, t_data *img, char *line, int *i)
{
	ray->pos_x = img->map_x + 0.5;
	ray->pos_y = *i + 0.5;
	ray->plane_y = 0;
	ray->dir_x = 0;
	if (line[*i] == 'W')
	{
		ray->plane_x = -1;
		ray->dir_y = -0.66;
	}
	if (line[*i] == 'E')
	{
		ray->plane_x = 1;
		ray->dir_y = 0.66;
	}
	img->map[img->map_x][*i] = '0';
	img->flags.pl++;
}

void	ft_count_sprite(t_data *img, char *line, int *i)
{
	int	j;

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
	*i = j;
	free(line);
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
	img->map_x = 0;
	while (img->map_x < img->size)
	{
		img->map_y = 0;
		while (img->map_y < img->max_len)
		{
			if (img->map[img->map_x][img->map_y] != '1'
			&& img->map[img->map_x][img->map_y] != '2'
			&& img->map[img->map_x][img->map_y] != '0'
			&& img->map[img->map_x][img->map_y] != ' '
			&& img->map[img->map_x][img->map_y] != '\t'
			&& img->map[img->map_x][img->map_y] != 'N'
			&& img->map[img->map_x][img->map_y] != 'E'
			&& img->map[img->map_x][img->map_y] != 'W'
			&& img->map[img->map_x][img->map_y] != 'S')
				ft_errors("wrong map");
			img->map_y++;
		}
		img->map_x++;
	}
	if (img->flags.r == 0 || img->flags.t != 5 || img->flags.c == 0)
		ft_errors("not enought data");
}
