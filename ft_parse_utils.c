/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:17:12 by paminna           #+#    #+#             */
/*   Updated: 2021/04/01 15:20:51 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_resolution(char *line, t_data *img,
								unsigned int *w, unsigned int *h)
{
	int j;

	j = 0;
	if (ft_isdigit(line[j]))
	{
		*w = ft_atoi((const char *)&(line[j]));
		img->flags.r++;
	}
	while (ft_isdigit(line[j]))
		j++;
	while (line[j] == ' ')
		j++;
	if (ft_isdigit(line[j]))
	{
		*h = ft_atoi((const char *)&(line[j]));
		img->flags.r++;
	}
	while (ft_isdigit(line[j]))
		j++;
	while (line[j] == ' ')
		j++;
	if (ft_isdigit(line[j]))
		ft_errors("Wrong resolution");
}

void	ft_check_r(char *line, int *i, int *r, t_data *img)
{
	int j;

	j = *i;
	if (ft_isdigit(line[j]))
		*r = ft_atoi(&line[j]);
	else
		ft_errors("wrong color");
	while (ft_isdigit(line[j]))
		j++;
	while (line[j] == ' ')
		j++;
	if (line[j] == ',')
	{
		j++;
		img->flags.coma = 1;
	}
	while (line[j] == ' ')
		j++;
	*i = j;
}

void	ft_check_g(char *line, int *i, int *g, t_data *img)
{
	int j;

	j = *i;
	if (ft_isdigit(line[j]) && (img->flags.coma == 1))
		*g = ft_atoi(&line[j]);
	else
		ft_errors("wrong color");
	while (ft_isdigit(line[j]))
		j++;
	while (line[j] == ' ')
		j++;
	if (line[j] == ',')
	{
		j++;
		img->flags.coma = 2;
	}
	while (line[j] == ' ')
		j++;
	*i = j;
}

void	ft_check_b_and_other(char *line, int *i, int *b, t_data *img)
{
	int j;

	j = *i;
	if (ft_isdigit(line[j]) && (img->flags.coma == 2))
		*b = ft_atoi(&line[j]);
	else
		ft_errors("wrong color");
	while (ft_isdigit(line[j]))
		j++;
	while (line[j] != '\0')
	{
		if (ft_isdigit(line[j]) || line[j++] == ',')
			ft_errors("wrong color");
		j++;
	}
	*i = j;
}

void	ft_full_matrix(t_data *img, char *line)
{
	int i;

	i = 0;
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
}
