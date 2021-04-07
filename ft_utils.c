/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:27:28 by paminna           #+#    #+#             */
/*   Updated: 2021/04/07 10:59:09 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_string(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])) &&
		!(str[i] == 32 || (str[i] > 8 && str[i] < 14)))
			ft_errors("Wrong symbols");
		i++;
	}
}

void	ft_condition_of_parse(char *line, t_data *img, t_ray *ray)
{
	if (line[0] == 'R' && (line[1] == ' ' || line[1] == '\t'))
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
		ft_parse_color(line, &ray->c, img);
	else if (line[0] == 'F' && line[1] == ' ')
		ft_parse_color(line, &ray->f, img);
	else if ((line[0] == ' ' || line[0] == '0'
	|| line[0] == '1' || (line[0] > 8 && line[0] < 14)))
		ft_parse_map(line, ray, img);
	else if (line[0] == '\0' && img->flags.map_start != 0)
		ft_errors("wrong data in file");
}

void	ft_init_img(t_data *img)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (!(img->sides[i].img = mlx_xpm_file_to_image(img->mlx,
		img->sides[i].side, &img->sides[i].width, &img->sides[i].height)))
			ft_errors("Wrong textures");
		img->sides[i].addr = mlx_get_data_addr(img->sides[i].img,
		&img->sides[i].bits_per_pixel, &img->sides[i].line_length,
		&img->sides[i].endian);
		i++;
	}
}

void	ft_check_file(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i -= 4;
	if (str[i] != '.' && str[i] != 'c' && str[i] != 'u' && str[i] != 'b')
		ft_errors("wrong type of file");
	if ((i = open(str, O_DIRECTORY)) > 0)
		ft_errors("file is a directory");
	if ((i = open(str, O_RDONLY)) < 0)
	{
		ft_errors("Can't open file");
		close(i);
	}
}

void	ft_initialize(t_data *img)
{
	img->win.img = NULL;
	img->win.addr = NULL;
	img->win.bits_per_pixel = 0;
	img->win.endian = 0;
	img->win.line_length = 0;
	img->map_x = 0;
	img->map_y = 0;
	img->ray.camera_x = 0;
	img->ray.hit = 0;
	img->ray.lineheight = 0;
	img->ray.perp_wall_dist = 0;
	img->ray.side = 0;
	img->spr.num_sprites = 0;
	img->spr.sprite_count = 0;
	img->flags.r = 0;
	img->max_len = -1;
	img->size = 0;
	img->flags.coma = 0;
	img->color = 0;
	img->flags.count_c = 0;
	img->flags.t = 0;
	img->flags.c = 0;
	img->flags.pl = 0;
	img->flags.map_start = 0;
}
