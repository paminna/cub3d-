/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:27:28 by paminna           #+#    #+#             */
/*   Updated: 2021/04/01 15:28:56 by paminna          ###   ########.fr       */
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
		ft_parse_color(line, &ray->c, img);
	else if (line[0] == 'F' && line[1] == ' ')
		ft_parse_color(line, &ray->f, img);
	else if (line[0] == ' ' || line[0] == '0'
	|| line[0] == '1' || (line[0] > 8 && line[0] < 14))
		ft_parse_map(line, ray, img);
}
