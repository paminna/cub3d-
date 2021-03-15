/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:09 by paminna           #+#    #+#             */
/*   Updated: 2021/03/15 18:26:16 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_errors(char *ans)
{
	while (*ans != '\0')
		write(1, &(*ans++), 1);
	exit(0);
}

void 	ft_parse_resolution(t_data *img, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == 'R')
		i++;
	if (ft_isdigit(line[i]))
		img->win.width = ft_atoi((const char *)&(line[i]));
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		img->win.height = ft_atoi((const char *)&(line[i]));
		i++;
	}
	if (img->win.width > 4096)
		img->win.width = 4096;
	if (img->win.height > 2304)
		img->win.height = 2304;
	if (img->win.height < 0 || img->win.width < 0)
		ft_errors("Error wrong resolution");
}

void ft_parse_tex(char*line, char **side)
{
	int i;
	int j;
	// char *tex;
	int fd;

	i = 0;
	j = 0;
	if ((*side) != NULL)
		ft_errors("double tex");
	// if ((tex = (char*)malloc(ft_strlen(line) + 1)) == 0)
	// 	ft_errors("Malloc error");
	while (line[i] != '.' && line[i+1] != '/')
		i++;
	if (line[i] == '\0')
		ft_errors("Wrong textures");
	*side = ft_strtrim(&line[i], " ");
	if ((fd = open(*side, O_RDONLY)) < 0)
		ft_errors("Error Wrong textures");
	// *side = tex;
	// free(tex);
	close(fd);
}

void ft_parse_color(char *line, int *side)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	b = 0;
	while (ft_isalpha(line[i]) || line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		g = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		b = ft_atoi(&line[i]);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ft_errors("Color error");
	*side = (1 << 24 | r << 16 | g << 8 | b);
}

void	ft_parse_map(char *line, t_ray *ray, t_data *img)
{
	int i;

	i = 0;
	img->map[img->mapX] = ft_strdup(line);
	while (line[i] != '\0')
	{
		if (line[i]== 'N' || line[i]== 'S')
		{
			ray->posX = img->mapX;
			ray->posY = i;
			ray->planeX = 0;
			ray->dirY = 0;
			if (line[i]== 'N')
			{
				ray->planeY = 0.66;
				ray->dirX = -1;
			}
			if (line[i]== 'S')
			{
				ray->planeY = -0.66;
				ray->dirX = 1;
			}
			img->map[img->mapX][i] = '0';
		}
		if (line[i]== 'W' || line[i]== 'E')
		{
			ray->posX = img->mapX;
			ray->posY = i;
			ray->planeY = 0;
			ray->dirX = 0;
		
			if (line[i]== 'W')
			{
				ray->planeX = -1;
				ray->dirY = -0.66;
			}
			if (line[i]== 'E')
			{
				ray->planeX = 1;
				ray->dirY = 0.66;
			}
			img->map[img->mapX][i] = '0';
		}
		if (line[i]== '2')
		{
			img->one[i].x = img->mapX;
			img->one[i].y = i;
			img->sprites.num_sprites++;
		}
		i++;
	}
	img->mapX++;
}


void ft_count_lines(t_data *img)
{
	int fd;
	int size;
	char *line;
	int i;

	size = 0;
	i = 0;
	fd = open("map.cub", O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		if ((line[i] == '1' || line[i] == '0') && (line[i] != '\0'))
		{
			while (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'W' 
			|| line[i] == 'E' || line[i] == 'S' || line[i] == '2')
				i++;
			size++;
			i = 0;
		}
	}
	close(fd);
	img->map = (char**)malloc((size+1) * sizeof(char*));
}

// void ft_init_tex(t_data *img)
// {
// 	img->tex.no = NULL;
// 	img->tex.so = NULL;
// 	img->tex.we = NULL;
// 	img->tex.ea = NULL;
// 	img->tex.s = NULL;
// }

void ft_parser(t_ray *ray, t_data *img)
{
	char *line;
	int fd;

	ft_count_lines(img);
	// ft_init_tex(img);
	img->tex.side = NULL;
	fd = open("map.cub", O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		if (line[0] == 'R' && line[1] == ' ')
			ft_parse_resolution(img, line);
		if (line[0] == 'N' && line[1] == 'O')
			ft_parse_tex(line, &(img->sides[0].side));
		if (line[0] == 'S' && line[1] == 'O')
			ft_parse_tex(line, &(img->sides[1].side));
		if (line[0] == 'W' && line[1] == 'E')
			ft_parse_tex(line, &(img->sides[2].side));
		if (line[0] == 'E' && line[1] == 'A')
			ft_parse_tex(line, &(img->sides[3].side));
		if (line[0] == 'S' && line[1] == ' ')
			ft_parse_tex(line, &(img->sides[4].side));
		if (line[0] == 'C' && line[1] == ' ')
			ft_parse_color(line,&ray->c);
		if (line[0] == 'F' && line[1] == ' ')
			ft_parse_color(line,&ray->f);
		if (line[0] == '0' || line[0] == '1')
			ft_parse_map(line, ray, img);
		free(line);
	}
	ft_parse_map(line, ray, img);
	free(line);
}