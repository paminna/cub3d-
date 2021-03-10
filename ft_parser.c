/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:09 by paminna           #+#    #+#             */
/*   Updated: 2021/03/10 19:07:54 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_data	*make_map(t_list **head, int size, t_data *img)
// {
// 	int		  i = -1;
// 	t_list	*tmp = *head;

// 	img->map = ft_calloc(size + 1, sizeof(char *));
// 	while (tmp)
// 	{
// 		img->map[++i] = tmp->content;
// 		tmp= tmp->next;
// 	}
// 	img->map[++i] = NULL;
// 	return (img);
// }

void ft_errors(char *ans)
{
	while (*ans != '\0')
		write(1, &(*ans++), 1);
	exit(0);
}

void 	ft_parse_resolution(t_ray *ray, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == 'R')
		i++;
	if (ft_isdigit(line[i]))
		ray->width = ft_atoi((const char *)&(line[i]));
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		ray->height = ft_atoi((const char *)&(line[i]));
		i++;
	}
	if (ray->width > 4096)
		ray->width = 4096;
	if (ray->height > 2304)
		ray->height = 2304;
	if (ray->height < 0 || ray->width < 0)
		ft_errors("Error wrong resolution");
}

void ft_parse_tex(char *line, int *side)
{
	int i;
	int j;
	char *tex;

	i = 0;
	j = 0;
	if ((tex = (char*)malloc(ft_strlen(line) + 1)) == 0)
		ft_errors("Malloc error");
	while (line[i] != '.' && line[i+1] != '/')
		i++;
	while (ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '.' || line[i] == '/')
	{
		tex[j] = line[i];
		j++;
		i++;
	}
	tex[j] = '\0';
	if ((*side = open(tex, O_RDONLY)) < 0)
		ft_errors("Error Wrong textures");
}

// char *ft_make_str(int c, char *color, int i)
// {
// 	if (c == 0)
// 	{
// 		color[i++] = '0';
// 		color[i++] = '0';
// 	}
// 	i += 3;
// 	while (c != 0)
// 	{
// 		color[i--] = "0123456789ABCDEF"[c % 16];
// 		c /= 16;
// 	}
// 	// printf("color in f |%s|\n", color);
// 	return (color);
// }

// char *ft_convert(int r, int g, int b)
// {
// 	char *color;
// 	int ans;
// 	int i;
// 	char help[10];

// 	i = 0;
// 	// color = (char*)malloc(11);
// 	// if (color == 0)
// 	// 	ft_errors("wrong malloc");
// 	help[0] = '0';
// 	help[1] = 'x';
// 	// printf("color %s", color);
// 	i = 2;
// 	color = ft_make_str(r,&color[i], i);
// 	// ans = ft_atoi((const char*)color);
// 	color = ft_make_str(g,&color[i], i);
// 	// ans = ft_atoi((const char*)color);
// 	color = ft_make_str(b,&color[i], i);
// 	// ans = ft_atoi((const char*)color);
// 	// if (r == 0)
// 	// {
// 	// 	color[i] = '0';
// 	// 	color[i+1] = '0';
// 	// }
// 	// while (r != 0)
// 	// {
// 	// 	color[i--] = "0123456789abcdef"[r % 16];
// 	// 	r /= 16;
// 	// }
// 	printf("color %s", color);
// 	return(color);
// }


void ft_parse_color(char *line, int *side)
{
	int r;
	int g;
	int b;
	int i;
	// char * color;

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
	// color = ft_convert(r, g, b);
	*side = (1 << 24 | r << 16 | g << 8 | b);
}

void	ft_parse_map(char *line, t_ray *ray, t_data *img)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		img->map[img->mapX][img->mapY] = line[i];
		if (line[i]== 'N' || line[i]== 'S')
		{
			ray->posX = img->mapX;
			ray->posY = img->mapY;
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
			img->map[img->mapX][img->mapY] = '0';
		}
		if (line[i]== 'W' || line[i]== 'E')
		{
			ray->posX = img->mapX;
			ray->posY = img->mapY;
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
			img->map[img->mapX][img->mapY] = '0';
		}
		img->mapX++;
		i++;
	}
	img->mapY++;
	img->mapX = 0;
}

void ft_parser(t_ray *ray, t_data *img)
{
	char *line;
	int fd;
	// int width;
	// int height;

	// width = 0;
	// height = 0;
	fd = open("map.cub", O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		if (line[0] == 'R' && line[1] == ' ')
			ft_parse_resolution(ray, line);
		if (line[0] == 'N' && line[1] == 'O')
			ft_parse_tex(line, &ray->no);
		if (line[0] == 'S' && line[1] == 'O')
			ft_parse_tex(line, &ray->so);
		if (line[0] == 'W' && line[1] == 'E')
			ft_parse_tex(line, &ray->we);
		if (line[0] == 'E' && line[1] == 'A')
			ft_parse_tex(line, &ray->ea);
		if (line[0] == 'C' && line[1] == ' ')
			ft_parse_color(line, &ray->c);
		if (line[0] == 'F' && line[1] == ' ')
			ft_parse_color(line, &ray->f);
		if (line[0] == '0' || line[0] == '1')
			ft_parse_map(line, ray, img);
	}
}