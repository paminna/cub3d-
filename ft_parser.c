/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:09 by paminna           #+#    #+#             */
/*   Updated: 2021/03/28 21:20:22 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_errors(char *ans)
{
	while (*ans != '\0')
		write(1, &(*ans++), 1);
	exit(0);
}

void ft_check_string(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])) && !(str[i] == 32 || (str[i] > 8 && str[i] < 14)))
			ft_errors("Wrong symbols");
		i++;
	}
}

void 	ft_parse_resolution(t_data *img, char *line)
{
	int i;

	i = 0;
	if (img->flags.r == 0)
		img->flags.r = 1;
	else
		ft_errors("double resolution");
	while (line[i] == ' ' || (line[i] == 32 || (line[i] > 8 && line[i] < 14)) || line[i] == 'R')
		i++;
	ft_check_string(&line[i]);
	if (ft_isdigit(line[i]))
	{
		img->win.width = ft_atoi((const char *)&(line[i]));
		img->flags.r++;
	}
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		img->win.height = ft_atoi((const char *)&(line[i]));
		img->flags.r++;
	}
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		ft_errors("Wrong resolution");
	if (img->win.width > 4096)
		img->win.width = 4096;
	if (img->win.height > 2304)
		img->win.height = 2304;
	if (img->win.height < 0 || img->win.width < 0)
		ft_errors("Error wrong resolution");
}

void ft_parse_tex(char*line, char **side, t_data *img)
{
	int i;
	int j;
	int fd;

	i = 0;
	j = 0;
	if ((*side) != NULL)
		ft_errors("double tex");
	if (ft_isalnum(line[3]))
		ft_errors("wrong line in tex");
	while (line[i] != '.' && line[i+1] != '/')
	{
		
		i++;
	}
	if (line[i] == '\0')
		ft_errors("Wrong textures");
	*side = ft_strtrim(&line[i], " ");
	if ((fd = open(*side, O_RDONLY)) < 0)
		ft_errors("Error Wrong textures");
	close(fd);
	img->flags.t++;
}

void ft_parse_color(char *line, int *side, t_data *img)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	b = 0;
	if ((*side) != 0)
		ft_errors("double color");
	while (line[i] != '\0')
	{
		if (!(ft_isdigit(line[i])) && line[i] != 'C' && line[i] != 'F' && line[i] != ' ' && line[i] != ',')
			ft_errors("wrong symbols in color");
		i++;
	}
	i = 0;
	while (line[i] == 'C' || line[i] == 'F' || line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		r = ft_atoi(&line[i]);
		// img->flags.count_c++;
	}
	else
		ft_errors("wrong color");
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
	{
		i++;
		img->flags.coma = 1;
	}
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i])&& (img->flags.coma == 1))
		g = ft_atoi(&line[i]);
	else
		ft_errors("wrong color");
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
	{
		i++;
		img->flags.coma = 2;
	}
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]) && (img->flags.coma == 2))
		b = ft_atoi(&line[i]);
	else
		ft_errors("wrong color");
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) || line[i] == ',')
			ft_errors("wrong color");
		i++;
	}
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ft_errors("Color error");
	*side = (1 << 24 | r << 16 | g << 8 | b);
	img->flags.c++;
}

void	ft_parse_map(char *line, t_ray *ray, t_data *img)
{
	int i;

	i = 0;
	if (img->flags.t != 5 || img->flags.c != 2)
		ft_errors("wrong data in file");
	img->mapY = 0;
	img->map[img->mapX] = (char*)malloc(img->max_len + 1);
	while (img->mapY < img->max_len)
	{
		while (img->mapY < (int)ft_strlen(line))
		{
			img->map[img->mapX][img->mapY] = line[i++];
			img->mapY++;
		}
		if (img->mapY < img->max_len)
			img->map[img->mapX][img->mapY] = ' ';
		img->mapY++;
		img->map[img->mapX][img->mapY] = '\0';
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i]== 'N' || line[i]== 'S')
		{
			ray->posX = img->mapX + 0.5;
			ray->posY = i  + 0.5;
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
			img->flags.pl++;
		}
		if (line[i]== 'W' || line[i]== 'E')
		{
			ray->posX = img->mapX + 0.5;
			ray->posY = i + 0.5;
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
			img->flags.pl++;
		}
		if (line[i] == '2')
		{
			img->one[img->sprites.sprite_count].x = (double)img->mapX + 0.5;
			img->one[img->sprites.sprite_count].y = (double)i  + 0.5;
			img->sprites.sprite_count++;
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
	img->sprites.num_sprites = 0;
	fd = open("map.cub", O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		if ((int)ft_strlen(line) > img->max_len)
			img->max_len = (int)ft_strlen(line);
		if ((line[i] == '1' || line[i] == '2'|| line[i] == '0' || line[i] == ' ' || line[i] == 32 || (line[i] > 8 && line[i] < 14)) && (line[i] != '\0'))
		{
			while (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S')
				i++;
			while (line[i++] == '2')
				img->sprites.num_sprites++;
			img->size++;
			i = 0;
		}
	}
	img->size++;
	close(fd);
	if (!(img->map = (char**)malloc((img->size+1) * sizeof(char*))))
		ft_errors("Malloc error");
	if (!(img->one = (t_ones*)malloc(sizeof(t_ones) * (img->sprites.num_sprites))))
		ft_errors("Malloc error");
}

void ft_check_map(t_data *img)
{
	img->mapY = 0;
	img->mapX = 0;
	while (img->mapX < img->size)
	{
		while (img->mapY < img->max_len)
		{
			if (img->map[img->mapX][img->mapY] != '1' && img->map[img->mapX][img->mapY] != '2' 
			&& img->map[img->mapX][img->mapY] != '0' && img->map[img->mapX][img->mapY] != ' '
			&& img->map[img->mapX][img->mapY] != '\t'
			&& img->map[img->mapX][img->mapY] != 'N' && img->map[img->mapX][img->mapY] != 'E' 
			&& img->map[img->mapX][img->mapY] != 'W' && img->map[img->mapX][img->mapY] != 'S')
				ft_errors("wrong map");
			img->mapY++;
		}
		img->mapY = 0;
		img->mapX++;
	}
	if (img->flags.r == 0 || img->flags.t != 5 || img->flags.c == 0)
		ft_errors("not enought data");
}

void ft_parser(t_ray *ray, t_data *img, char *file)
{
	char *line;
	int fd;

	ft_count_lines(img);
	fd = open(file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		if (line[0] == 'R' && line[1] == ' ')
			ft_parse_resolution(img, line);
		else if (line[0] == 'N' && line[1] == 'O')
			ft_parse_tex(line, &(img->sides[0].side), img);
		else if (line[0] == 'S' && line[1] == 'O')
			ft_parse_tex(line, &(img->sides[1].side), img);
		else if (line[0] == 'W' && line[1] == 'E')
			ft_parse_tex(line, &(img->sides[2].side), img);
		else if (line[0] == 'E' && line[1] == 'A')
			ft_parse_tex(line, &(img->sides[3].side), img);
		else if (line[0] == 'S' && line[1] == ' ')
			ft_parse_tex(line, &(img->sides[4].side), img);
		else if (line[0] == 'C' && line[1] == ' ')
			ft_parse_color(line,&ray->c, img);
		else if (line[0] == 'F' && line[1] == ' ')
			ft_parse_color(line,&ray->f, img);
		else if (line[0] == ' ' || line[0] == '0' || line[0] == '1' || (line[0] > 8 && line[0] < 14))
			ft_parse_map(line, ray, img);
		free(line);
	}
	ft_parse_map(line, ray, img);
	free(line);
	ft_check_map(img);
	if (img->flags.pl != 1)
		ft_errors("Wrong amount player");
}