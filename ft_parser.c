/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:09 by paminna           #+#    #+#             */
/*   Updated: 2021/03/06 19:09:55 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*make_map(t_list **head, int size, t_data *img)
{
	int		  i = -1;
	t_list	*tmp = *head;

	img->map = ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		img->map[++i] = tmp->content;
		tmp= tmp->next;
	}
	img->map[++i] = NULL;
	return (img);
}
// int		ft_find_numbers(char *str)
// {
// 	int i;
// 	int numb;
	
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (ft_isdigit(str[i]))
// 			numb = ft_atoi(&str[i]);
// 		i++;
// 	}
// 	return (numb);
// }

// int		ft_find_color(char *str)
// {
// 	int i;
// 	int color;
	
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '0' && str[i+1] == 'x')
// 		{
// 			i = i + 2;
// 			while (ft_isdigit(str[i]))
// 				color = ft_atoi(&str[i]);
// 		}
// 		i++;
// 	}
// 	return (color);
// }

// void ft_parser(t_data *img, t_ray *ray)
// {
// 	int fd;
// 	char *str;
// 	int i;
	
// 	i = 0;
// 	str = NULL;
// 	fd = open("map.cub", O_RDONLY);
// 	while (get_next_line(fd, &str) != 0 && str[0] != '0' && str[1] != '1')
// 	{
// 		if (str[0] == 'R' && str[1] == ' ')
// 			img->width = ft_find_numbers(&str[0]);
// 		if (str[0] == 'N' && str[1] == 'O')
// 			img->no = ft_find_color(&str[0]);
// 		if (str[0] == 'S' && str[1] == 'O')
// 			img->so = ft_find_color(&str[0]);
// 		if (str[0] == 'W' && str[1] == 'E')
// 			img->we = ft_find_color(&str[0]);
// 		if (str[0] == 'E' && str[1] == 'A')
// 			img->ea = ft_find_color(&str[0]);
// 		if (str[0] == 'C' && str[1] == ' ')
// 			img->c = ft_find_color(&str[0]);
// 		if (str[0] == 'F' && str[1] == ' ')
// 			img->f = ft_find_color(&str[0]);
// 	}
// 	while (get_next_line(fd, &str) != 0)
// 	{
// 		while ((str[i] != '0' || str[i] != '1'))
// 			i++;
// 		while (str[i] != '\0')
// 		{
// 			if (str[i] == '1' && str[i] == '0')
// 				img->map[img->mapX][img->mapY] = str[i];
// 			if (str[i] == 'N')
// 			{
// 				ray->planeX = 0;
// 				ray->planeY = 0.66;
// 				ray->dirX = -1;
// 				ray->dirY = 0;
// 			}
// 			if (str[i] == 'S')
// 			{
// 				ray->planeX = 0;
// 				ray->planeY = -0.66;
// 				ray->dirX = 1;
// 				ray->dirY = 0;
// 			}
// 			if (str[i] == 'E')
// 			{
				
// 			}
// 			if (str[i] == 'W')
// 			{
				
// 			}
// 		}
// 	}
// }