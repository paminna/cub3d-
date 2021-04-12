/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:09 by paminna           #+#    #+#             */
/*   Updated: 2021/04/07 20:02:03 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_resolution(t_data *img, char *line)
{
	int				i;
	unsigned int	w;
	unsigned int	h;

	i = 0;
	if (img->flags.r == 0)
		img->flags.r = 1;
	else
		ft_errors("double resolution");
	while (line[i] == ' ' ||
	(line[i] == 32 || (line[i] > 8 && line[i] < 14)) || line[i] == 'R')
		i++;
	ft_check_string(&line[i]);
	ft_check_resolution(&line[i], img, &w, &h);
	if (w > 2560)
		w = 2560;
	if (h > 1400)
		h = 1400;
	img->win.width = (int)w;
	img->win.height = (int)h;
	if (img->win.height <= 0 || img->win.width <= 0)
		ft_errors("Error wrong resolution");
}

void	ft_parse_tex(char *line, char **side, t_data *img)
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
	while (line[i] != '.' && line[i + 1] != '/')
		i++;
	if (line[i] == '\0')
		ft_errors("Wrong textures");
	*side = ft_strtrim(&line[i], " ");
	if ((fd = open(*side, O_RDONLY)) < 0)
		ft_errors("Error Wrong textures");
	close(fd);
	img->flags.t++;
}

void	ft_parse_color(char *line, int *side, t_data *img)
{
	int r;
	int g;
	int b;
	int i;

	i = 0;
	if ((*side) != 0)
		ft_errors("double color");
	while (line[i] != '\0')
	{
		if (!(ft_isdigit(line[i])) && line[i] != 'C'
		&& line[i] != 'F' && line[i] != ' ' && line[i] != ',')
			ft_errors("wrong symbols in color");
		i++;
	}
	i = 0;
	while (line[i] == 'C' || line[i] == 'F' || line[i] == ' ')
		i++;
	ft_check_r(line, &i, &r, img);
	ft_check_g(line, &i, &g, img);
	ft_check_b_and_other(line, &i, &b, img);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ft_errors("Color error");
	*side = (1 << 24 | r << 16 | g << 8 | b);
	img->flags.c++;
}

void	ft_parse_map(char *line, t_ray *ray, t_data *img)
{
	int i;

	i = 0;
	img->flags.map_start++;
	if (img->flags.t != 5 || img->flags.c != 2)
		ft_errors("wrong data in file");
	img->map_y = 0;
	img->map[img->map_x] = (char*)malloc(img->max_len + 1);
	ft_full_matrix(img, line);
	while (line[i] != '\0')
	{
		if (line[i] == 'N' || line[i] == 'S')
			ft_find_pl(ray, img, line, &i);
		else if (line[i] == 'W' || line[i] == 'E')
			ft_find_pl_2(ray, img, line, &i);
		else if (line[i] == '2')
		{
			img->one[img->spr.sprite_count].x = (double)img->map_x + 0.5;
			img->one[img->spr.sprite_count].y = (double)i + 0.5;
			img->spr.sprite_count++;
		}
		i++;
	}
	img->map_x++;
}

void	ft_parser(t_ray *ray, t_data *img, char *file)
{
	char	*line;
	int		fd;

	ft_count_lines(img);
	fd = open(file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) != 0)
	{
		ft_condition_of_parse(line, img, ray);
		free(line);
	}
	ft_parse_map(line, ray, img);
	free(line);
	ft_check_map(img);
	if (img->flags.pl != 1)
		ft_errors("Wrong amount player");
}
